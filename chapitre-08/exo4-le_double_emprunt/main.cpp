// Chapitre 8 - Exercice 4 : Le double emprunt
//
// On montre ce que rendent AcquireImage et ReleaseImage quand on les appelle
// deux fois de suite. Un emprunt refuse ne touche pas la variable de
// l'appelant : elle garde sa valeur d'avant, choisie par le hasard.
//
// Entree : n v N, puis N ordres (acquire X, release, last)
// Compilation : clang++ -std=c++17 -Wall main.cpp -o programme

#include <array>
#include <cstdint>
#include <iostream>
#include <string>

struct Chaine {
    std::uint32_t nombreImages;
    std::uint32_t prochaine = 0;
    bool empruntee = false;

    // Ecrit l'index dans 'index' seulement si l'emprunt reussit
    bool AcquireImage(std::uint32_t& index){
        if (empruntee) return false;
        index = prochaine;
        empruntee = true;
        return true;
    }

    bool ReleaseImage(){
        if (!empruntee) return false;
        prochaine = (prochaine + 1) % nombreImages;
        empruntee = false;
        return true;
    }

    std::uint32_t GetLastReleasedIndex() const {
        return (prochaine + nombreImages - 1) % nombreImages;
    }
};

int main(){
    std::uint32_t n, v;
    long long N;
    if (!(std::cin >> n >> v >> N)) return 1;

    Chaine chaine{ n };
    std::array<std::uint32_t, 26> variables;  // une variable par lettre a..z
    variables.fill(v);

    for (long long i = 0; i < N; ++i){
        std::string ordre;
        if (!(std::cin >> ordre)) break;

        if (ordre == "acquire"){
            char lettre;
            std::cin >> lettre;
            std::uint32_t& x = variables[lettre - 'a'];
            const bool ok = chaine.AcquireImage(x);
            std::cout << "ACQUIRE " << (ok ? "VRAI " : "FAUX ") << lettre << " " << x << "\n";
        }
        else if (ordre == "release"){
            std::cout << "RELEASE " << (chaine.ReleaseImage() ? "VRAI" : "FAUX") << "\n";
        }
        else if (ordre == "last"){
            std::cout << "LAST " << chaine.GetLastReleasedIndex() << "\n";
        }
    }

    std::cout << "EMPRUNTEE " << (chaine.empruntee ? "OUI" : "NON") << "\n";
    std::cout << "PROCHAINE " << chaine.prochaine << "\n";
    return 0;
}
