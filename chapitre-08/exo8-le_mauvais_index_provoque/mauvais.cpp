// Chapitre 8 - Exercice 8 : Le mauvais index, provoque
//
// On simule une chaine de n images ou la soumission lit l'index de la derniere
// image relachee a differents moments, et l'on mesure ce que l'oeil voit quand
// la camera avance de v millimetres par trame.
//   A : on soumet l'index emprunte
//   P : on lit (prochaine + n - 1) % n AVANT ReleaseImage -> image de la trame d'avant
//   D : on lit (prochaine + n - 1) % n APRES ReleaseImage -> image que l'on vient de peindre
//
// Entree : n T x0 v, puis un mot de T lettres (A, P ou D)
// Compilation : clang++ -std=c++17 -Wall mauvais.cpp -o mauvais

#include <iostream>
#include <string>
#include <vector>

int main(){
    long long n, T, x0, v;
    std::string modes;
    if (!(std::cin >> n >> T >> x0 >> v)) return 1;
    if (T > 0 && !(std::cin >> modes)) return 1;   // avec T = 0, le mot est vide
    if (static_cast<long long>(modes.size()) < T) modes.resize(T, 'A');

    std::vector<long long> trameDansEmplacement(n, 0);  // derniere trame peinte, 0 au depart
    long long prochaine = 0;

    bool precedenteMontree = false;   // la trame precedente a-t-elle montre une position ?
    long long positionPrecedente = 0;
    bool auMoinsUnSaut = false;
    long long sautMin = 0, sautMax = 0;

    for (long long t = 1; t <= T; ++t){
        const char mode = modes[t - 1];

        // On emprunte la prochaine image et l'on y peint la trame t
        const long long empruntee = prochaine;
        trameDansEmplacement[empruntee] = t;

        long long soumis = empruntee;                       // mode A
        if (mode == 'P') soumis = (prochaine + n - 1) % n;  // lu avant la liberation

        // ReleaseImage
        prochaine = (prochaine + 1) % n;
        if (mode == 'D') soumis = (prochaine + n - 1) % n;  // lu apres la liberation

        const long long f = trameDansEmplacement[soumis];
        if (f == 0){
            std::cout << t << " NOIR -\n";
            precedenteMontree = false;
            continue;
        }

        const long long position = x0 + v * f;
        std::cout << t << " " << position << " ";
        if (t == 1 || !precedenteMontree){
            std::cout << "-\n";
        } else {
            const long long saut = position - positionPrecedente;
            std::cout << saut << "\n";
            if (!auMoinsUnSaut || saut < sautMin) sautMin = saut;
            if (!auMoinsUnSaut || saut > sautMax) sautMax = saut;
            auMoinsUnSaut = true;
        }
        precedenteMontree = true;
        positionPrecedente = position;
    }

    if (!auMoinsUnSaut){
        std::cout << "SAUTS AUCUN\n";
    } else {
        std::cout << "SAUT MIN " << sautMin << "\n";
        std::cout << "SAUT MAX " << sautMax << "\n";
        std::cout << "TREMBLE " << (sautMin != sautMax ? "OUI" : "NON") << "\n";
    }
    return 0;
}
