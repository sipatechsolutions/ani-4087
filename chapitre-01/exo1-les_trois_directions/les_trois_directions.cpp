// Chapitre 2 - Exercice 1 : Les trois directions
//
// Trois fonctions fixent la convention du module une fois pour toutes :
//   Avant()  = +Z, Haut() = +Y, Droite() = +X  (vecteurs unitaires).
// Le programme lit trois reels (un point), et affiche son produit scalaire
// avec chacune des trois directions. Trois lignes, quatre decimales.
//
// Compilation : g++ -std=c++17 -O2 les_trois_directions.cpp -o directions
// Execution   : echo "1 2 3" | ./directions

#include <cstdio>

struct Vec3 { double x, y, z; };

static double dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// La convention du module, fixee ici une fois pour toutes :
Vec3 Avant()  { return {0.0, 0.0, 1.0}; } // +Z : l'avant
Vec3 Haut()   { return {0.0, 1.0, 0.0}; } // +Y : le haut
Vec3 Droite() { return {1.0, 0.0, 0.0}; } // +X : la droite

int main() {
    Vec3 p;
    if (std::scanf("%lf %lf %lf", &p.x, &p.y, &p.z) != 3) {
        std::fprintf(stderr, "Entree attendue : trois reels (x y z)\n");
        return 1;
    }
    std::printf("%.4f\n", dot(p, Avant()));
    std::printf("%.4f\n", dot(p, Haut()));
    std::printf("%.4f\n", dot(p, Droite()));
    return 0;
}
