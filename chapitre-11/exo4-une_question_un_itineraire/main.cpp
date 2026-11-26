// Chapitre 11 - Exercice 4 : une question, un itineraire
// Du registre a la bibliotheque du runtime : on ouvre le manifeste designe
// par le registre, on y scanne la cle "library_path" (sans lecteur JSON),
// puis on resout le chemin relatif au dossier du manifeste.
#include <iostream>
#include <string>

static const char kAntislash = 92;   // l'antislash (code ASCII 92)

static std::string lireLigne() {
    std::string s;
    if (!std::getline(std::cin, s)) return "";
    if (!s.empty() && s.back() == '\r') s.pop_back();
    return s;
}

int main() {
    long long k = 0;
    try { k = std::stoll(lireLigne()); } catch (...) { k = 0; }

    for (long long i = 1; i <= k; ++i) {
        std::string registre = lireLigne();
        long long l = 0;
        try { l = std::stoll(lireLigne()); } catch (...) { l = 0; }
        std::string texte;
        for (long long j = 0; j < l; ++j) texte += lireLigne() + "\n";

        if (registre == "-") {
            std::cout << i << " REGISTRE AUCUN\n";
            continue;
        }
        std::cout << i << " MANIFESTE " << registre << '\n';
        if (l < 0) { std::cout << i << " ECHEC ILLISIBLE\n"; continue; }

        const std::string cle = "\"library_path\"";
        std::size_t p = texte.find(cle);
        if (p == std::string::npos) { std::cout << i << " ECHEC CLE\n"; continue; }
        std::size_t deuxPoints = texte.find(':', p + cle.size());
        if (deuxPoints == std::string::npos) { std::cout << i << " ECHEC DEUX_POINTS\n"; continue; }
        std::size_t g1 = texte.find('"', deuxPoints);
        std::size_t g2 = (g1 == std::string::npos) ? g1 : texte.find('"', g1 + 1);
        if (g2 == std::string::npos) { std::cout << i << " ECHEC GUILLEMET\n"; continue; }

        // Recopie signe par signe ; un antislash suivi d'un antislash est saute.
        std::string valeur;
        for (std::size_t c = g1 + 1; c < g2; ++c) {
            if (texte[c] == kAntislash && c + 1 < g2 && texte[c + 1] == kAntislash) continue;
            valeur += texte[c];
        }
        if (valeur.empty()) { std::cout << i << " ECHEC VIDE\n"; continue; }
        std::cout << i << " VALEUR " << valeur << '\n';

        bool absolu = (valeur.size() >= 2 && valeur[1] == ':') ||
                      valeur[0] == kAntislash || valeur[0] == '/';
        if (absolu) {
            std::cout << i << " ABSOLU\n" << i << " CHARGE " << valeur << '\n';
        } else {
            std::size_t sep = registre.find_last_of(std::string(1, kAntislash) + "/");
            std::string dossier = (sep == std::string::npos) ? "" : registre.substr(0, sep + 1);
            std::cout << i << " RELATIF\n" << i << " CHARGE " << dossier << valeur << '\n';
        }
    }
    return 0;
}
