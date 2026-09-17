// Chapitre 1 - Exercice 1 : Les trois cadences
//
// Calcule la duree d'une image a 72, 90 et 120 Hz (au dixieme de ms),
// puis retire les 8 ms prises par le materiel (capteurs + transmission
// + composition + affichage) pour donner ce qu'il reste au code.
//
// Compilation : g++ -std=c++17 -O2 les_trois_cadences.cpp -o cadences
// Execution   : ./cadences

#include <cstdio>

int main() {
    const double overhead_ms = 8.0;          // capteurs + transmission + composition + affichage
    const int    cadences[]  = {72, 90, 120};

    std::printf("Frequence | Image (ms) | Reste au code (ms)\n");
    std::printf("----------+------------+-------------------\n");
    for (int hz : cadences) {
        double image = 1000.0 / hz;          // duree d'une image
        double code  = image - overhead_ms;  // budget restant au code
        std::printf("%7d Hz | %10.1f | %18.1f\n", hz, image, code);
    }
    return 0;
}
