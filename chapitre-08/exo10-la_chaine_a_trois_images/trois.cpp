// Chapitre 8 - Exercice 10 : La chaine a trois images
//
// La trame u (de 1 a T) peint l'image (u - 1) % n puis la soumet ; le
// compositeur lit cette image pendant les L trames suivantes. La trame u est en
// conflit si l'image qu'elle peint a ete soumise par l'une des trames u-1 a u-L
// (numeros 1 ou plus) : elle peint alors une image que le compositeur affiche.
//
// Entree : K, puis K scenarios "n L T"
// Compilation : clang++ -std=c++17 -Wall trois.cpp -o trois

#include <iostream>

int main(){
    long long K;
    if (!(std::cin >> K)) return 1;

    for (long long s = 0; s < K; ++s){
        long long n, L, T;
        if (!(std::cin >> n >> L >> T)) break;

        std::cout << "CIBLES " << n << " " << L;
        long long conflits = 0;
        for (long long u = 1; u <= T; ++u){
            const long long image = (u - 1) % n;
            std::cout << " " << image;

            // L'image est-elle encore lue ? Une trame comptee au plus une fois.
            bool enConflit = false;
            for (long long v = u - 1; v >= 1 && v >= u - L; --v){
                if ((v - 1) % n == image){ enConflit = true; break; }
            }
            if (enConflit) ++conflits;
        }
        std::cout << "\n";
        std::cout << "CONFLITS " << n << " " << L << " " << conflits << "\n";
    }
    return 0;
}
