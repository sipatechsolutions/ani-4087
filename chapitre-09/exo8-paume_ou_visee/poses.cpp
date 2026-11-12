// Chapitre 9 - Exercice 8 : paume ou visee
// Place la paume et la visee de chaque main dans la salle, pour plusieurs
// poses de tete, puis cherche l'objet que chacune pourrait saisir.
// La paume tient les objets ; la visee pointe.
#include <cmath>
#include <iostream>
#include <vector>

struct Vec3 {
    long long x = 0;
    long long y = 0;
    long long z = 0;
};

// Repere de la tete -> salle : on tourne (x, z) de k quarts de tour,
// puis on ajoute la position de la tete.
static Vec3 versSalle(const Vec3& local, const Vec3& tete, int k) {
    long long x = local.x, z = local.z, rx = x, rz = z;
    switch (((k % 4) + 4) % 4) {
        case 0: rx = x;  rz = z;  break;
        case 1: rx = z;  rz = -x; break;
        case 2: rx = -x; rz = -z; break;
        default: rx = -z; rz = x; break;
    }
    Vec3 r;
    r.x = rx + tete.x;
    r.y = local.y + tete.y;
    r.z = rz + tete.z;
    return r;
}

static long long distance2(const Vec3& a, const Vec3& b) {
    long long dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return dx * dx + dy * dy + dz * dz;
}

static void afficher(const char* nom, const Vec3& p) {
    std::cout << nom << ' ' << p.x << ' ' << p.y << ' ' << p.z << '\n';
}

// Objet le plus proche a 150 mm au plus ; 0 si aucun.
static int saisie(const Vec3& main, const std::vector<Vec3>& objets) {
    int meilleur = 0;
    long long meilleureDistance = 0;
    for (std::size_t j = 0; j < objets.size(); ++j) {
        long long d2 = distance2(main, objets[j]);
        if (d2 <= 22500 && (meilleur == 0 || d2 < meilleureDistance)) {
            meilleur = static_cast<int>(j) + 1;
            meilleureDistance = d2;
        }
    }
    return meilleur;
}

static void afficherSaisie(const char* nom, int j) {
    std::cout << "SAISIE " << nom << ' ';
    if (j == 0) std::cout << "AUCUNE\n";
    else std::cout << j << '\n';
}

int main() {
    int h = 0, m = 0;
    if (!(std::cin >> h >> m)) return 0;

    std::vector<Vec3> tetes(h);
    std::vector<int> lacets(h);
    for (int i = 0; i < h; ++i) {
        std::cin >> tetes[i].x >> tetes[i].y >> tetes[i].z >> lacets[i];
    }
    std::vector<Vec3> objets(m);
    for (Vec3& o : objets) std::cin >> o.x >> o.y >> o.z;

    // Poses dans le repere de la tete (main droite) ; la gauche inverse x
    // AVANT la rotation.
    const Vec3 paumeD{180, -300, -250};
    const Vec3 viseeD{180, -250, -400};
    const Vec3 paumeG{-180, -300, -250};
    const Vec3 viseeG{-180, -250, -400};

    Vec3 dernierePaume, derniereVisee;
    for (int i = 0; i < h; ++i) {
        Vec3 pd = versSalle(paumeD, tetes[i], lacets[i]);
        Vec3 vd = versSalle(viseeD, tetes[i], lacets[i]);
        Vec3 pg = versSalle(paumeG, tetes[i], lacets[i]);
        Vec3 vg = versSalle(viseeG, tetes[i], lacets[i]);

        std::cout << "TETE " << (i + 1) << '\n';
        afficher("PAUME D", pd);
        afficher("VISEE D", vd);
        afficher("PAUME G", pg);
        afficher("VISEE G", vg);
        afficherSaisie("PAUME", saisie(pd, objets));
        afficherSaisie("VISEE", saisie(vd, objets));
        dernierePaume = pd;
        derniereVisee = vd;
    }

    double ecart = std::sqrt(static_cast<double>(distance2(dernierePaume, derniereVisee)));
    std::cout << "ECART " << std::llround(ecart) << '\n';
    return 0;
}
