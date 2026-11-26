// Chapitre 11 - Exercice 6 : le champ, isole
// Le choix du backend se decide une fois, a l'initialisation. On cherche les
// lignes de la boucle ou de la scene qui le testent quand meme (fuites), et
// les definis de disponibilite utilises hors de la fabrique.
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static bool signeDeMot(char c) {
    return std::isalnum(static_cast<unsigned char>(c)) || c == '_';
}

// Le nom apparait-il entier (ni lettre, ni chiffre, ni _ autour) ?
static bool contientNom(const std::string& texte, const std::string& nom) {
    if (nom.empty()) return false;
    std::size_t pos = 0;
    while ((pos = texte.find(nom, pos)) != std::string::npos) {
        bool avantOk = pos == 0 || !signeDeMot(texte[pos - 1]);
        std::size_t fin = pos + nom.size();
        bool apresOk = fin >= texte.size() || !signeDeMot(texte[fin]);
        if (avantOk && apresOk) return true;
        ++pos;
    }
    return false;
}

static bool contientUn(const std::string& texte, const std::vector<std::string>& noms) {
    for (const std::string& n : noms) {
        if (contientNom(texte, n)) return true;
    }
    return false;
}

static std::vector<std::string> lireNoms(const std::string& ligne) {
    std::istringstream flux(ligne);
    std::string lettre;
    int k = 0;
    flux >> lettre >> k;
    std::vector<std::string> noms;
    for (int i = 0; i < k; ++i) {
        std::string n;
        if (flux >> n) noms.push_back(n);
    }
    return noms;
}

static std::string lireLigne() {
    std::string s;
    if (!std::getline(std::cin, s)) return "";
    if (!s.empty() && s.back() == '\r') s.pop_back();
    return s;
}

int main() {
    std::vector<std::string> choix = lireNoms(lireLigne());
    std::vector<std::string> definis = lireNoms(lireLigne());
    long long n = 0;
    try { n = std::stoll(lireLigne()); } catch (...) { n = 0; }

    long long decisions = 0, fuites = 0, definisHors = 0;
    for (long long l = 1; l <= n; ++l) {
        std::string ligne = lireLigne();
        std::size_t espace = ligne.find(' ');
        std::string zone = ligne.substr(0, espace);
        std::string texte = (espace == std::string::npos) ? "" : ligne.substr(espace + 1);

        std::size_t debut = texte.find_first_not_of(" \t");
        if (debut != std::string::npos && texte.compare(debut, 2, "//") == 0) continue;

        if (contientUn(texte, choix)) {
            if (zone == "INIT") {
                ++decisions;
            } else if (zone == "BOUCLE" || zone == "SCENE") {
                std::cout << "FUITE " << l << ' ' << zone << '\n';
                ++fuites;
            }
        }
        if (zone != "FABRIQUE" && contientUn(texte, definis)) {
            std::cout << "DEFINI " << l << ' ' << zone << '\n';
            ++definisHors;
        }
    }

    std::cout << "DECISIONS " << decisions << '\n';
    std::cout << "FUITES " << fuites << '\n';
    std::cout << "DEFINIS " << definisHors << '\n';
    std::cout << "ABSTRACTION " << (fuites == 0 && definisHors == 0 ? "TENUE" : "FUIT") << '\n';
    return 0;
}
