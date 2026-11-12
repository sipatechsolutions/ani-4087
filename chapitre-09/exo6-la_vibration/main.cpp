// Chapitre 9 - Exercice 6 : la vibration
// ApplyHaptic(amplitude, duree, frequence) : dans cet ordre.
// Une vibration se veut courte (50 a 200 ms) ; inverser duree et
// frequence donne une manette qui vibre des minutes.
#include <iostream>
#include <string>

int main() {
    long long n = 0;
    if (!(std::cin >> n)) n = 0;

    long long bonnes = 0, longues = 0, muettes = 0;
    long long temps = 0;   // 64 bits : le total peut depasser un int

    for (long long i = 1; i <= n; ++i) {
        long long a = 0, d = 0, f = 0;
        std::cin >> a >> d >> f;

        long long amplitude = a < 0 ? 0 : (a > 100 ? 100 : a);
        std::string duree = d > 0 ? std::to_string(d) : "MIN";
        std::string frequence = f > 0 ? std::to_string(f) : "DEFAUT";
        if (d > 0) temps += d;

        std::string verdict;
        if (amplitude == 0) {
            verdict = "MUETTE";
            ++muettes;
        } else if (d < 50) {
            verdict = "BREVE";
        } else if (d <= 200) {
            verdict = "BONNE";
            ++bonnes;
        } else {
            verdict = "LONGUE";
            ++longues;
        }

        std::cout << i << ' ' << amplitude << ' ' << duree << ' ' << frequence
                  << ' ' << verdict << '\n';
    }

    std::cout << "BONNES " << bonnes << '\n';
    std::cout << "LONGUES " << longues << '\n';
    std::cout << "MUETTES " << muettes << '\n';
    std::cout << "TEMPS " << temps << '\n';
    return 0;
}
