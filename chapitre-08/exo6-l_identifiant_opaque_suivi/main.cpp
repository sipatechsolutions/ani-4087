// Chapitre 8 - Exercice 6 : L'identifiant opaque, suivi
//
// La chaine range des poignees de textures (entiers de 64 bits) sans savoir ce
// qu'elles designent (SetImageNative / GetImageNative). Si la texture est
// detruite, la chaine rend quand meme le vieux nombre : c'est au moment du get
// qu'on verifie si la texture existe encore.
//
// Entree : n N, puis N ordres (cree h, detruit h, set i h, get i)
// Compilation : clang++ -std=c++17 -Wall main.cpp -o programme

#include <cstdint>
#include <iostream>
#include <set>
#include <string>
#include <vector>

static const std::uint64_t MAX_32_BITS = 4294967295ULL;

int main(){
    std::uint64_t n;
    long long N;
    if (!(std::cin >> n >> N)) return 1;

    std::vector<std::uint64_t> emplacements(n, 0);  // poignees rangees, 0 au depart
    std::set<std::uint64_t> texturesVivantes;

    long long mortes = 0, larges = 0;

    for (long long i = 0; i < N; ++i){
        std::string ordre;
        if (!(std::cin >> ordre)) break;

        if (ordre == "cree"){
            std::uint64_t h;
            std::cin >> h;
            texturesVivantes.insert(h);   // deja existante : aucun effet
        }
        else if (ordre == "detruit"){
            std::uint64_t h;
            std::cin >> h;
            texturesVivantes.erase(h);    // inexistante : aucun effet
        }
        else if (ordre == "set"){
            std::uint64_t index, h;
            std::cin >> index >> h;
            if (index >= n){
                std::cout << "SET IGNORE " << index << "\n";
            } else {
                emplacements[index] = h;
                if (h > MAX_32_BITS) ++larges;
            }
        }
        else if (ordre == "get"){
            std::uint64_t index;
            std::cin >> index;
            const std::uint64_t h = (index < n) ? emplacements[index] : 0;

            // L'emplacement garde le vieux nombre : l'existence se verifie maintenant
            if (h == 0){
                std::cout << "GET " << index << " 0 VIDE\n";
            } else if (texturesVivantes.count(h)){
                std::cout << "GET " << index << " " << h << " VIVANTE\n";
            } else {
                std::cout << "GET " << index << " " << h << " MORTE\n";
                ++mortes;
            }
        }
    }

    std::cout << "MORTES " << mortes << "\n";
    std::cout << "LARGES " << larges << "\n";
    return 0;
}
