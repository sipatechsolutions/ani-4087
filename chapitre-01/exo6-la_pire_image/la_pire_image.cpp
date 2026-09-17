// Chapitre 1 - Exercice 6 : La pire image
//
// Programme qui "efface l'ecran" en boucle (remplit un framebuffer 1920x1080
// d'une couleur unie a chaque image). Sur 1000 images, on mesure :
//   - la duree de la PLUS LONGUE image (la "pire image"),
//   - le nombre d'images qui depassent 11 ms.
// On juge une experience en casque a sa pire image, pas a sa cadence moyenne.
//
// Compilation : g++ -std=c++17 -O2 la_pire_image.cpp -o pire_image
// Execution   : ./pire_image

#include <chrono>
#include <cstdio>
#include <cstdint>
#include <vector>

using clk = std::chrono::steady_clock;

int main() {
    const int W = 1920, H = 1080;      // resolution simulee (~2,07 Mpx)
    const int N = 1000;                // nombre d'images mesurees
    std::vector<uint32_t> framebuffer(static_cast<size_t>(W) * H); // ~8,3 Mo

    double pire  = 0.0;                 // duree max (ms)
    int    depass = 0;                  // images > 11 ms
    double total = 0.0;                 // somme pour la moyenne
    volatile uint32_t sink = 0;         // empeche l'optimiseur de tout supprimer

    for (int i = 0; i < N; ++i) {
        auto t0 = clk::now();

        // "Effacer l'ecran" : remplir tout le framebuffer d'une couleur unie
        uint32_t couleur = 0xFF000000u | static_cast<uint32_t>(i); // change chaque image
        for (size_t p = 0; p < framebuffer.size(); ++p) framebuffer[p] = couleur;
        sink ^= framebuffer[static_cast<size_t>(i) % framebuffer.size()];

        auto t1 = clk::now();
        double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();

        total += ms;
        if (ms > pire) pire = ms;
        if (ms > 11.0) ++depass;
    }

    std::printf("Images mesurees     : %d\n", N);
    std::printf("Duree moyenne       : %.3f ms\n", total / N);
    std::printf("Pire image          : %.3f ms\n", pire);
    std::printf("Images > 11 ms      : %d / %d\n", depass, N);
    std::printf("Tiendrait en casque : %s\n", depass == 0 ? "OUI" : "NON");
    (void)sink;
    return 0;
}
