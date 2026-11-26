// Chapitre 11 - Exercice 8 : l'environnement, a un seul endroit
// Les reglages sont des champs poses par le code. Les variables
// d'environnement n'entrent que par une seule fonction, qui applique ici les
// regles exactes du module, y compris ses surprises (False allume).
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

struct Reglages {
    std::string backend = "SIMULATEUR";
    long long hz = 0;
    bool demi = false;
    bool profondeur = false;
    bool liste = false;
    std::string loader = "-";
    long long latence = 0;
    bool poseFixe = false;
    long long pose[5] = {0, 0, 0, 0, 0};
};

static std::string lireLigne() {
    std::string s;
    if (!std::getline(std::cin, s)) return "";
    if (!s.empty() && s.back() == '\r') s.pop_back();
    return s;
}

// Lit un entier a partir de pos : espaces, signe facultatif, chiffres.
// Avance pos et dit s'il y avait au moins un chiffre.
static long long lireNombre(const std::string& t, std::size_t& pos, bool& chiffre) {
    while (pos < t.size() && t[pos] == ' ') ++pos;
    bool negatif = false;
    if (pos < t.size() && (t[pos] == '+' || t[pos] == '-')) {
        negatif = t[pos] == '-';
        ++pos;
    }
    long long n = 0;
    chiffre = false;
    while (pos < t.size() && std::isdigit(static_cast<unsigned char>(t[pos]))) {
        n = n * 10 + (t[pos] - '0');
        chiffre = true;
        ++pos;
    }
    return negatif ? -n : n;
}

static bool interrupteur(const std::string& v) {
    return !(v[0] == '0' || v == "false");
}

// La seule porte d'entree des variables : rend true si la variable a pose une valeur.
static bool appliquer(Reglages& r, const std::string& nom, const std::string& v) {
    if (v.empty()) return false;
    if (nom == "NK_XR_BACKEND") {
        if (v != "openxr") return false;
        r.backend = "OPENXR";
        return true;
    }
    if (nom == "NK_XR_HZ" || nom == "NK_XR_SIM_LATENCY_MS") {
        std::size_t pos = 0;
        bool chiffre = false;
        long long n = lireNombre(v, pos, chiffre);
        (nom == "NK_XR_HZ" ? r.hz : r.latence) = n;
        return true;
    }
    if (nom == "NK_XR_HALF_RATE") { r.demi = interrupteur(v); return true; }
    if (nom == "NK_XR_DEPTH_LAYER") { r.profondeur = interrupteur(v); return true; }
    if (nom == "NK_XR_LIST_EXT") { r.liste = interrupteur(v); return true; }
    if (nom == "NK_XR_OPENXR_LOADER") { r.loader = v; return true; }
    if (nom == "NK_XR_SIM_POSE") {
        long long lus[5];
        int compte = 0;
        std::size_t pos = 0;
        while (compte < 5 && pos < v.size()) {
            bool chiffre = false;
            long long n = lireNombre(v, pos, chiffre);
            if (!chiffre) break;
            lus[compte++] = n;
            while (pos < v.size() && (v[pos] == ',' || v[pos] == ' ')) ++pos;
        }
        if (compte != 5) return false;
        r.poseFixe = true;
        for (int i = 0; i < 5; ++i) r.pose[i] = lus[i];
        return true;
    }
    return false;   // nom non lu
}

static const char* ouiNon(bool b) { return b ? "OUI" : "NON"; }

int main() {
    Reglages r;
    {
        std::istringstream l1(lireLigne());
        std::string demi, prof, liste;
        l1 >> r.backend >> r.hz >> demi >> prof >> liste >> r.latence;
        r.demi = demi == "OUI";
        r.profondeur = prof == "OUI";
        r.liste = liste == "OUI";
    }
    r.loader = lireLigne();
    {
        std::istringstream l3(lireLigne());
        std::string mode;
        l3 >> mode;
        if (mode == "FIXE") {
            r.poseFixe = true;
            for (long long& p : r.pose) l3 >> p;
        }
    }

    long long m = 0;
    try { m = std::stoll(lireLigne()); } catch (...) { m = 0; }
    long long appliquees = 0, ignorees = 0;
    for (long long i = 0; i < m; ++i) {
        std::string ligne = lireLigne();
        std::size_t egal = ligne.find('=');
        std::string nom = ligne.substr(0, egal);
        std::string valeur = (egal == std::string::npos) ? "" : ligne.substr(egal + 1);
        if (appliquer(r, nom, valeur)) ++appliquees;
        else ++ignorees;
    }

    std::cout << "BACKEND " << r.backend << '\n';
    std::cout << "HZ " << r.hz << '\n';
    std::cout << "DEMI " << ouiNon(r.demi) << '\n';
    std::cout << "PROFONDEUR " << ouiNon(r.profondeur) << '\n';
    std::cout << "LISTE " << ouiNon(r.liste) << '\n';
    std::cout << "LOADER " << r.loader << '\n';
    std::cout << "LATENCE " << r.latence << '\n';
    if (r.poseFixe) {
        std::cout << "POSE FIXE";
        for (long long p : r.pose) std::cout << ' ' << p;
        std::cout << '\n';
    } else {
        std::cout << "POSE LIBRE\n";
    }
    std::cout << "APPLIQUEES " << appliquees << '\n';
    std::cout << "IGNOREES " << ignorees << '\n';
    return 0;
}
