// Chapitre 11 - Exercice 3 : le type opaque
// Suit les inclusions par niveaux depuis chaque unite .cpp et dit si elle
// atteint un en-tete externe (comme openxr.h), avec le chemin qui y mene.
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

static bool finitParCpp(const std::string& nom) {
    return nom.size() >= 4 && nom.compare(nom.size() - 4, 4, ".cpp") == 0;
}

int main() {
    int e = 0;
    if (!(std::cin >> e)) return 0;
    std::set<std::string> externes;
    for (int i = 0; i < e; ++i) {
        std::string nom;
        std::cin >> nom;
        externes.insert(nom);
    }

    int f = 0;
    std::cin >> f;
    std::vector<std::string> ordre;                      // fichiers, ordre d'entree
    std::map<std::string, std::vector<std::string>> inclut;
    for (int i = 0; i < f; ++i) {
        std::string nom;
        int k = 0;
        std::cin >> nom >> k;
        std::vector<std::string> liste(k > 0 ? k : 0);
        for (std::string& x : liste) std::cin >> x;
        ordre.push_back(nom);
        inclut[nom] = liste;
    }

    int touchees = 0, unites = 0;
    for (const std::string& unite : ordre) {
        if (!finitParCpp(unite)) continue;
        ++unites;

        // Parcours en largeur : niveau par niveau, dans l'ordre des #include.
        std::map<std::string, std::string> parent;
        std::set<std::string> vus = {unite};
        std::queue<std::string> file;
        file.push(unite);
        std::string trouve;

        while (!file.empty() && trouve.empty()) {
            std::string courant = file.front();
            file.pop();
            auto it = inclut.find(courant);
            if (it == inclut.end()) continue;            // systeme ou externe : rien
            for (const std::string& suivant : it->second) {
                if (vus.count(suivant)) continue;        // deja rencontre
                vus.insert(suivant);
                parent[suivant] = courant;
                if (externes.count(suivant)) { trouve = suivant; break; }
                file.push(suivant);
            }
        }

        if (trouve.empty()) {
            std::cout << unite << " NON\n";
            continue;
        }
        ++touchees;
        std::vector<std::string> chemin;
        for (std::string n = trouve; ; n = parent[n]) {
            chemin.push_back(n);
            if (n == unite) break;
        }
        std::cout << unite << " OUI ";
        for (std::size_t i = chemin.size(); i-- > 0;) {
            std::cout << chemin[i] << (i > 0 ? ">" : "");
        }
        std::cout << '\n';
    }
    std::cout << "TOUCHEES " << touchees << " SUR " << unites << '\n';
    return 0;
}
