// Chapitre 1 - Exercice 7 : Le cout du doublement
//
// Reprend le programme de l'exercice 6 et separe :
//   - la LOGIQUE (mise a jour d'objets)  -> faite UNE fois par image
//   - le RENDU    (remplir le framebuffer) -> a faire DEUX fois en VR (un par oeil)
// On mesure le rendu SEUL, puis on estime son cout x2 et ce qu'il resterait
// dans le budget d'une image a 90 Hz (~11,1 ms).
//
// Compilation : g++ -std=c++17 -O2 le_cout_du_doublement.cpp -o cout
// Execution   : ./cout

#include <chrono>
#include <cstdio>
#include <cstdint>
#include <vector>

using clk = std::chrono::steady_clock;
static double ms(clk::time_point a, clk::time_point b) {
    return std::chrono::duration<double, std::milli>(b - a).count();
}

int main() {
    const int W = 1920, H = 1080;
    const int N = 1000;
    std::vector<uint32_t> framebuffer(static_cast<size_t>(W) * H); // ~8,3 Mo

    // "Monde" a faire evoluer dans la logique (ne se double PAS en VR)
    const int NB = 200000;
    std::vector<float> x(NB), v(NB);
    for (int i = 0; i < NB; ++i) { x[i] = 0.0f; v[i] = 0.001f * i; }

    double rendu_total = 0.0, logique_total = 0.0;
    volatile uint32_t sink = 0; volatile float fsink = 0.0f;

    for (int i = 0; i < N; ++i) {
        // --- LOGIQUE (une fois) ---
        auto l0 = clk::now();
        for (int k = 0; k < NB; ++k) { x[k] += v[k]; if (x[k] > 1000.0f) x[k] = 0.0f; }
        fsink += x[i % NB];
        auto l1 = clk::now();
        logique_total += ms(l0, l1);

        // --- RENDU SEUL (a doubler en VR) ---
        auto r0 = clk::now();
        uint32_t couleur = 0xFF000000u | static_cast<uint32_t>(i);
        for (size_t p = 0; p < framebuffer.size(); ++p) framebuffer[p] = couleur;
        sink ^= framebuffer[static_cast<size_t>(i) % framebuffer.size()];
        auto r1 = clk::now();
        rendu_total += ms(r0, r1);
    }

    double rendu   = rendu_total   / N;   // rendu seul, moyenne (ms)
    double logique = logique_total / N;   // logique seule, moyenne (ms)
    double rendu_2x = rendu * 2.0;        // estimation VR : un rendu par oeil

    const double budget90 = 1000.0 / 90.0;            // 11,1 ms par image a 90 Hz
    const double overhead = 8.0;                       // materiel (capteurs+transm.+compo+affichage)
    double budget_code = budget90 - overhead;          // ~3,1 ms pour tout le code
    double reste_apres_2x = budget_code - (rendu_2x + logique);

    std::printf("--- Mesures (moyenne sur %d images) ---\n", N);
    std::printf("Rendu SEUL (1x)        : %.3f ms\n", rendu);
    std::printf("Logique (1x)           : %.3f ms\n", logique);
    std::printf("--- Estimation VR ---\n");
    std::printf("Rendu DOUBLE (2x)      : %.3f ms\n", rendu_2x);
    std::printf("Rendu 2x + logique     : %.3f ms\n", rendu_2x + logique);
    std::printf("Budget image 90 Hz     : %.3f ms\n", budget90);
    std::printf("Budget code (-8 ms)    : %.3f ms\n", budget_code);
    std::printf("Reste apres rendu 2x   : %.3f ms\n", reste_apres_2x);
    (void)sink; (void)fsink;
    return 0;
}
