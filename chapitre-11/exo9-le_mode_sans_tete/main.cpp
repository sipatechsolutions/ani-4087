// Chapitre 11 - Exercice 9 : le mode sans tete
// Sans fenetre, la pose du simulateur ne bouge pas, mais l'instant predit
// vient de l'horloge. On compare deux executions : instants bruts, instants
// comptes depuis la premiere image, et instants scriptes (t x periode).
#include <iostream>
#include <string>
#include <vector>

int main() {
    long long hz = 0;
    std::cin >> hz;
    if (hz <= 1) hz = 72;
    const long long periode = 1000000000LL / hz;

    std::string mode;
    std::cin >> mode;
    long long pose[5] = {0, 0, 0, 1700, 0};   // pose de depart : lacet, tangage, x, y, z
    if (mode == "FIXE") {
        for (long long& p : pose) std::cin >> p;
    }

    long long t = 0;
    std::cin >> t;
    if (t < 0) t = 0;
    std::vector<long long> a(t), b(t);
    for (long long& v : a) std::cin >> v;
    for (long long& v : b) std::cin >> v;

    std::cout << "PERIODE " << periode << '\n';
    std::cout << "POSE " << pose[0] << ' ' << pose[1] << ' ' << pose[2] << ' '
              << pose[3] << ' ' << pose[4] << '\n';

    long long premierBrut = 0, premierRelatif = 0;
    for (long long i = 0; i < t; ++i) {
        long long predA = a[i] + periode;
        long long predB = b[i] + periode;
        long long brut = predB - predA;
        long long relatif = (predB - (b[0] + periode)) - (predA - (a[0] + periode));
        long long scripte = (i + 1) * periode;
        if (brut != 0 && premierBrut == 0) premierBrut = i + 1;
        if (relatif != 0 && premierRelatif == 0) premierRelatif = i + 1;
        std::cout << (i + 1) << " BRUT " << brut << " RELATIF " << relatif
                  << " SCRIPTE " << scripte << '\n';
    }

    if (premierBrut == 0) std::cout << "BRUT IDENTIQUE\n";
    else std::cout << "BRUT DIFFERENT " << premierBrut << '\n';
    if (premierRelatif == 0) std::cout << "RELATIF IDENTIQUE\n";
    else std::cout << "RELATIF DIFFERENT " << premierRelatif << '\n';
    return 0;
}
