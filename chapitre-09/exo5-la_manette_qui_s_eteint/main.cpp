// Chapitre 9 - Exercice 5 : la manette qui s'eteint
// Deux saisies sur les memes images : l'une teste active, l'autre non.
// Sans le test, l'extinction de la manette ressemble a un relachement.
#include <iostream>
#include <string>

int main() {
    long long t = 0;
    if (!(std::cin >> t)) t = 0;
    std::string signes;
    if (t > 0) std::cin >> signes;

    int precedent = 0;          // current avant l'image 1
    bool tenuAvec = false;
    bool tenuSans = false;
    bool parTerre = false;      // version SANS : l'objet est tombe
    long long prisesAvec = 0, prisesSans = 0, chutesSans = 0;
    long long coincesAvec = 0, differences = 0;

    for (long long i = 0; i < t && i < static_cast<long long>(signes.size()); ++i) {
        char s = signes[i];
        int active = (s == 'x') ? 0 : 1;
        int current = (s == '1') ? 1 : 0;
        int changed = (current != precedent) ? 1 : 0;
        precedent = current;

        bool appui = current == 1 && changed == 1;
        bool lacher = current == 0 && changed == 1;

        // Version AVEC : une action inactive ne change rien.
        if (active == 1) {
            if (appui) {
                tenuAvec = true;
                ++prisesAvec;
            } else if (lacher) {
                tenuAvec = false;
            }
        }

        // Version SANS : meme logique, sans regarder active.
        if (appui) {
            if (!parTerre) {
                tenuSans = true;
                ++prisesSans;
            }
        } else if (lacher) {
            if (tenuSans && active == 0) {
                parTerre = true;    // lache par l'extinction : chute
                ++chutesSans;
            }
            tenuSans = false;
        }

        if (s == '0' && tenuAvec) ++coincesAvec;
        if (tenuAvec != tenuSans) ++differences;

        std::cout << (i + 1) << ' ' << (tenuAvec ? "TENU" : "LIBRE") << ' '
                  << (tenuSans ? "TENU" : "LIBRE") << '\n';
    }

    std::cout << "PRISES AVEC " << prisesAvec << '\n';
    std::cout << "PRISES SANS " << prisesSans << '\n';
    std::cout << "CHUTES SANS " << chutesSans << '\n';
    std::cout << "COINCES AVEC " << coincesAvec << '\n';
    std::cout << "DIFFERENCES " << differences << '\n';
    return 0;
}
