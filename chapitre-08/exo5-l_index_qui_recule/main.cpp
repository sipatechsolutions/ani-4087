// Chapitre 8 - Exercice 5 : L'index qui recule
//
// On calcule l'index de la derniere image relachee de trois facons :
//   juste    : (prochaine + n - 1) % n            -> l'ecriture du moteur
//   signe    : (prochaine - 1) % n  en int        -> -1 % n vaut -1
//   nonsigne : (prochaine - 1) % n  en uint32_t   -> 0 - 1 vaut 4294967295
// Les deux ecritures courtes ne se trompent que quand prochaine vaut 0.
//
// Entree : N, puis N lignes "n r" (nombre d'images, liberations deja faites)
// Compilation : clang++ -std=c++17 -Wall main.cpp -o programme

#include <cstdint>
#include <iostream>

int main(){
    long long N;
    if (!(std::cin >> N)) return 1;

    long long refusees = 0, fauxSigne = 0, fauxNonSigne = 0;

    for (long long i = 0; i < N; ++i){
        std::uint64_t n, r;  // r peut depasser un int : lu sur 64 bits
        if (!(std::cin >> n >> r)) break;

        if (n == 0 || n > 4){
            std::cout << n << " " << r << " REFUSEE\n";
            ++refusees;
            continue;
        }

        const std::uint64_t prochaine = r % n;            // sur 64 bits
        const std::uint64_t juste = (prochaine + n - 1) % n;

        // Ecriture courte en entier signe : le reste d'un negatif est negatif
        const int prochaineInt = static_cast<int>(prochaine);
        const int nInt = static_cast<int>(n);
        const int signe = (prochaineInt - 1) % nInt;

        // Ecriture courte en non signe 32 bits : 0 - 1 boucle a 4294967295
        const std::uint32_t prochaine32 = static_cast<std::uint32_t>(prochaine);
        const std::uint32_t n32 = static_cast<std::uint32_t>(n);
        const std::uint32_t nonsigne = (prochaine32 - 1u) % n32;

        std::cout << n << " " << r << " " << prochaine << " " << juste << " "
                  << signe << " " << nonsigne << "\n";

        if (signe < 0 || static_cast<std::uint64_t>(signe) != juste) ++fauxSigne;
        if (static_cast<std::uint64_t>(nonsigne) != juste) ++fauxNonSigne;
    }

    std::cout << "REFUSEES " << refusees << "\n";
    std::cout << "FAUX SIGNE " << fauxSigne << "\n";
    std::cout << "FAUX NON SIGNE " << fauxNonSigne << "\n";
    return 0;
}
