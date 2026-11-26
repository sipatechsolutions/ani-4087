// Chapitre 11 - Exercice 10 : le test qui compare
// Une tete scriptee avance image par image ; on place les deux yeux le long
// de la droite de la tete, et l'instant vient d'une horloge scriptee (t x p),
// jamais de l'heure. La sortie est donc identique a chaque execution.
#include <iostream>

int main() {
    long long hz = 0, ipd = 0, n = 0;
    std::cin >> hz >> ipd >> n;
    long long x = 0, y = 0, z = 0, k0 = 0, dk = 0, vx = 0;
    std::cin >> x >> y >> z >> k0 >> dk >> vx;

    if (hz <= 1) hz = 72;
    const long long periode = 1000000000LL / hz;
    const long long demi = ipd / 2;
    std::cout << "PERIODE " << periode << '\n';

    // Droite de la tete au sol (x, z), selon le lacet en quarts de tour
    const long long droiteX[4] = {1, 0, -1, 0};
    const long long droiteZ[4] = {0, -1, 0, 1};

    for (long long t = 1; t <= n; ++t) {
        long long lacet = ((k0 + (t - 1) * dk) % 4 + 4) % 4;
        long long tx = x + (t - 1) * vx;
        long long gx = tx - demi * droiteX[lacet];
        long long gz = z - demi * droiteZ[lacet];
        long long dx = tx + demi * droiteX[lacet];
        long long dz = z + demi * droiteZ[lacet];
        long long instant = t * periode;   // horloge scriptee
        std::cout << t << " G " << gx << ' ' << y << ' ' << gz
                  << " D " << dx << ' ' << y << ' ' << dz
                  << " I " << instant << '\n';
    }
    return 0;
}
