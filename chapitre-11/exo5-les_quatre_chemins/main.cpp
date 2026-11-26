// Chapitre 11 - Exercice 5 : les quatre chemins
// Rejoue la recherche du casque : variable d'environnement, loader standard,
// decouverte directe, puis le repli vers le simulateur. Chaque bibliotheque
// ouverte pour rien est refermee, et l'application finit toujours sur un niveau.
#include <iostream>
#include <string>

int main() {
    int k = 0;
    if (!(std::cin >> k) || k <= 0) {
        std::cout << "AUCUNE MACHINE\n";
        return 0;
    }

    for (int i = 1; i <= k; ++i) {
        std::string d, v, l, r, b, g;
        std::cin >> d >> v >> l >> r >> b >> g;

        int chargees = 0, liberees = 0;
        bool chargee = false;      // une bibliotheque est ouverte en ce moment
        bool entree = false;       // on tient le point d'entree
        bool casque = false;       // backend OpenXR avec liaison reussie
        std::string source;

        // Une bibliotheque vient d'etre chargee : BON donne le point d'entree,
        // SANS la fait liberer aussitot.
        auto apresChargement = [&](const std::string& etat, const std::string& chemin) {
            ++chargees;
            chargee = true;
            if (etat == "BON") {
                entree = true;
                source = chemin;
            } else {
                std::cout << i << " SANS_ENTREE\n";
                ++liberees;
                chargee = false;
            }
        };

        if (d == "SIMULATEUR") {
            std::cout << i << " BACKEND SIMULATEUR DEMANDE\n";
        } else {
            // 1. La variable d'environnement
            if (v == "ABSENT") {
                std::cout << i << " VARIABLE IGNOREE\n";
            } else if (v != "-") {
                std::cout << i << " VARIABLE CHARGEE\n";
                apresChargement(v, "VARIABLE");
            }
            // 2. Le loader standard, seulement si rien n'a ete charge
            if (!entree && !chargee && liberees == 0 && chargees == 0) {
                if (l == "ABSENT") {
                    std::cout << i << " LOADER ABSENT\n";
                } else {
                    std::cout << i << " LOADER CHARGE\n";
                    apresChargement(l, "LOADER");
                }
            }
            // 3. La decouverte directe par le registre
            if (!entree) {
                std::cout << i << " DIRECT " << r << '\n';
                if (r == "NEGO_KO" || r == "BON") {
                    ++chargees;
                    chargee = true;
                }
                if (r == "BON") {
                    entree = true;
                    source = "DIRECT";
                }
            }
            // 4. Le backend
            if (!entree) {
                std::cout << i << " BACKEND INDISPONIBLE\n";
                if (chargee) { ++liberees; chargee = false; }
            } else {
                std::cout << i << " BACKEND OPENXR " << source << '\n';
                if (b == "NON") {
                    std::cout << i << " LIAISON ECHOUEE\n";
                    ++liberees;
                    chargee = false;
                } else {
                    casque = true;
                }
            }
        }

        // Le niveau : on ne s'arrete jamais
        if (casque) std::cout << i << " NIVEAU 1 CASQUE\n";
        else if (g == "OUI") std::cout << i << " NIVEAU 2 SIMULATEUR CARTE\n";
        else std::cout << i << " NIVEAU 3 SIMULATEUR LOGICIEL\n";
        std::cout << i << " CHARGEES " << chargees << " LIBEREES " << liberees << '\n';
    }
    return 0;
}
