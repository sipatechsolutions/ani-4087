// Chapitre 9 - Exercice 3 : les trois champs
// current, changed, active d'une action booleenne, image par image.
// Une action inactive vaut 0 : sans lire active, une manette eteinte
// ressemble a un relachement.
#include <iostream>
#include <string>

int main() {
    long long t = 0;
    if (!(std::cin >> t)) t = 0;
    std::string signes;
    if (t > 0) std::cin >> signes;

    int precedent = 0;   // current avant l'image 1
    long long appuis = 0, relaches = 0, fauxRelaches = 0, tenues = 0;

    for (long long i = 0; i < t && i < static_cast<long long>(signes.size()); ++i) {
        char s = signes[i];
        int active = (s == 'x') ? 0 : 1;
        int current = (s == '1') ? 1 : 0;
        int changed = (current != precedent) ? 1 : 0;

        if (current == 1 && changed == 1) ++appuis;
        if (current == 0 && changed == 1) {
            ++relaches;
            if (active == 0) ++fauxRelaches;
        }
        if (current == 1) ++tenues;

        std::cout << (i + 1) << ' ' << current << ' ' << changed << ' '
                  << active << '\n';
        precedent = current;
    }

    std::cout << "APPUIS " << appuis << '\n';
    std::cout << "RELACHES " << relaches << '\n';
    std::cout << "FAUX RELACHES " << fauxRelaches << '\n';
    std::cout << "TENUES " << tenues << '\n';
    return 0;
}
