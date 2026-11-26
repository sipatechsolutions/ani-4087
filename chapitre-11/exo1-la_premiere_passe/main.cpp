// Chapitre 11 - Exercice 1 : la premiere passe
// Lit l'en-tete d'un fichier source (le bloc de commentaires // du haut),
// s'arrete a la premiere ligne qui n'en est pas un, et liste les variables
// d'environnement NK_...= qu'il annonce.
#include <cctype>
#include <iostream>
#include <set>
#include <string>
#include <vector>

static bool estSigneNom(char c) {
    return std::isupper(static_cast<unsigned char>(c)) ||
           std::isdigit(static_cast<unsigned char>(c)) || c == '_';
}

static bool estSigneMot(char c) {
    return std::isalnum(static_cast<unsigned char>(c)) || c == '_';
}

int main() {
    std::string ligne;
    long long n = 0;
    if (!std::getline(std::cin, ligne)) ligne = "";
    try { n = std::stoll(ligne); } catch (...) { n = 0; }
    if (n < 0) n = 0;

    long long entete = 0;
    bool dansEntete = true;
    std::vector<std::string> variables;
    std::set<std::string> vues;

    for (long long i = 0; i < n; ++i) {
        if (!std::getline(std::cin, ligne)) ligne = "";
        if (!ligne.empty() && ligne.back() == '\r') ligne.pop_back();
        if (!dansEntete) continue;

        std::size_t debut = ligne.find_first_not_of(" \t");
        if (debut == std::string::npos || ligne.compare(debut, 2, "//") != 0) {
            dansEntete = false;   // fin de l'en-tete : le reste est ignore
            continue;
        }
        ++entete;

        // Chercher NK_<signes>= dans cette ligne d'en-tete
        std::size_t pos = 0;
        while ((pos = ligne.find("NK_", pos)) != std::string::npos) {
            bool debutMot = (pos == 0) || !estSigneMot(ligne[pos - 1]);
            std::size_t fin = pos + 3;
            while (fin < ligne.size() && estSigneNom(ligne[fin])) ++fin;
            if (debutMot && fin > pos + 3 && fin < ligne.size() && ligne[fin] == '=') {
                std::string nom = ligne.substr(pos, fin - pos);
                if (vues.insert(nom).second) variables.push_back(nom);
            }
            pos += 3;
        }
    }

    std::cout << "ENTETE " << entete << '\n';
    std::cout << "IGNOREES " << (n - entete) << '\n';
    if (variables.empty()) std::cout << "VARIABLE AUCUNE\n";
    for (const std::string& v : variables) std::cout << "VARIABLE " << v << '\n';
    std::cout << "PART " << (n > 0 ? 100 * entete / n : 0) << '\n';
    return 0;
}
