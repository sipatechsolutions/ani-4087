// Chapitre 9 - Exercice 4 : synchroniser une fois par image
// changed se calcule a la synchronisation : sans elle un front se repete,
// avec deux le second efface le premier. Sans le focus, l'appel est refuse.
#include <iostream>

struct EtatBool {
    int current = 0;
    int changed = 0;
    int active = 0;
};

int main() {
    long long t = 0;
    if (!(std::cin >> t)) t = 0;

    EtatBool etat;
    int pPrecedent = 0;   // p avant l'image 1
    long long appuisReels = 0, saisies = 0, refusees = 0;

    for (long long image = 1; image <= t; ++image) {
        int p = 0, s = 0, f = 0;
        std::cin >> p >> s >> f;

        for (int appel = 0; appel < s; ++appel) {
            if (f == 0) {           // SyncActions sans le focus : refuse
                ++refusees;
                continue;
            }
            etat.changed = (p != etat.current) ? 1 : 0;
            etat.current = p;
            etat.active = 1;
        }

        if (p == 1 && pPrecedent == 0) ++appuisReels;
        pPrecedent = p;

        bool saisit = etat.current == 1 && etat.changed == 1;
        if (saisit) ++saisies;

        std::cout << image << ' ' << etat.current << ' ' << etat.changed << ' '
                  << etat.active << ' ' << (saisit ? "SAISIT" : "-") << '\n';
    }

    std::cout << "APPUIS REELS " << appuisReels << '\n';
    std::cout << "SAISIES " << saisies << '\n';
    std::cout << "SYNC REFUSEES " << refusees << '\n';
    return 0;
}
