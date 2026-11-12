// Chapitre 9 - Exercice 10 : le deplacement au manche
// On deplace le joueur en decalant le monde, jamais en ecrivant la pose
// de la tete : celle-ci vient du casque et sert a la prediction.
#include <iostream>
#include <set>
#include <string>

struct Sol {
    long long x = 0;
    long long z = 0;
};

// Avant et droite de la tete, au sol, selon son lacet en quarts de tour.
static void axes(int k, Sol& avant, Sol& droite) {
    switch (((k % 4) + 4) % 4) {
        case 0: avant = {0, -1}; droite = {1, 0};  break;
        case 1: avant = {-1, 0}; droite = {0, -1}; break;
        case 2: avant = {0, 1};  droite = {-1, 0}; break;
        default: avant = {1, 0}; droite = {0, 1};  break;
    }
}

int main() {
    long long v = 0, t = 0;
    if (!(std::cin >> v >> t)) return 0;

    Sol decalage;            // decalage du joueur dans le monde
    long long diagonales = 0;

    for (long long image = 1; image <= t; ++image) {
        int k = 0, n = 0;
        std::cin >> k >> n;
        std::set<std::string> fleches;
        for (int j = 0; j < n; ++j) {
            std::string f;
            std::cin >> f;
            fleches.insert(f);
        }

        int x = (fleches.count("F_DROITE") ? 1 : 0) - (fleches.count("F_GAUCHE") ? 1 : 0);
        int y = (fleches.count("F_HAUT") ? 1 : 0) - (fleches.count("F_BAS") ? 1 : 0);
        if (x != 0 && y != 0) ++diagonales;

        Sol avant, droite;
        axes(k, avant, droite);   // la direction suit le lacet de CETTE image
        decalage.x += v * (y * avant.x + x * droite.x);
        decalage.z += v * (y * avant.z + x * droite.z);

        std::cout << image << ' ' << x << ',' << y << ' ' << decalage.x << ' '
                  << decalage.z << '\n';
    }

    std::cout << "DECALAGE " << decalage.x << ' ' << decalage.z << '\n';
    std::cout << "DIAGONALES " << diagonales << '\n';
    return 0;
}
