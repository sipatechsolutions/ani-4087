// Chapitre 11 - Exercice 2 : l'interface, comparee
// Compare les methodes publiques du backend du casque (liste A) et du
// simulateur (liste B) : ce qu'elles ont en commun, et ce qui n'est qu'a l'une.
#include <iostream>
#include <set>
#include <string>
#include <vector>

static std::vector<std::string> lireListe() {
    int n = 0;
    std::cin >> n;
    std::vector<std::string> noms;
    for (int i = 0; i < n; ++i) {
        std::string nom;
        if (std::cin >> nom) noms.push_back(nom);
    }
    return noms;
}

int main() {
    std::vector<std::string> a = lireListe();
    std::vector<std::string> b = lireListe();
    std::set<std::string> ensA(a.begin(), a.end());
    std::set<std::string> ensB(b.begin(), b.end());

    int communs = 0;
    for (const std::string& nom : ensA) {
        if (ensB.count(nom)) ++communs;
    }
    std::cout << "DEUX " << communs << '\n';

    int seuls = 0;
    std::set<std::string> deja;
    for (const std::string& nom : a) {
        if (!ensB.count(nom) && deja.insert(nom).second) {
            std::cout << "SEUL_A " << nom << '\n';
            ++seuls;
        }
    }
    for (const std::string& nom : b) {
        if (!ensA.count(nom) && deja.insert(nom).second) {
            std::cout << "SEUL_B " << nom << '\n';
            ++seuls;
        }
    }

    std::set<std::string> reunis = ensA;
    reunis.insert(ensB.begin(), ensB.end());
    std::cout << "DIFFERENTES " << seuls << " SUR " << reunis.size() << '\n';
    return 0;
}
