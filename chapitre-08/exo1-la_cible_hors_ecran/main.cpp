// Chapitre 8 - Exercice 1 : La cible hors ecran
//
// On suit la creation d'une cible hors ecran (CreateOffscreen), son branchement
// au rendu (SetFinalColorTarget) et la taille de la zone de rendu
// (SetRenderSizeOverride). Chaque image occupe le tampon (n - 1) % F.
// Une image dessinee vers une cible plus petite que la zone ne termine jamais
// son travail : son tampon reste pris, et la boucle se fige quand il revient.
//
// Entree : L H F N, puis N ordres (allume, cible, vers, taille, image)
// Compilation : clang++ -std=c++17 -Wall main.cpp -o programme

#include <iostream>
#include <string>
#include <vector>

struct Cible { long long largeur, hauteur; };

int main(){
    long long L, H;
    int F, N;
    if (!(std::cin >> L >> H >> F >> N)) return 1;

    bool offscreen = false;              // OFFSCREEN allume ?
    std::vector<Cible> cibles;           // cibles creees, numerotees a partir de 1
    long long destination = 0;           // 0 = fenetre, k = cible k
    long long zoneL = L, zoneH = H;      // zone de rendu, celle de la fenetre au depart
    std::vector<bool> tamponPris(F, false);
    long long numeroImage = 0;           // numero de la prochaine image - 1
    long long imagesDessinees = 0;
    bool bloque = false;

    for (int i = 0; i < N; ++i){
        std::string ordre;
        if (!(std::cin >> ordre)) break;

        // Les arguments sont lus meme apres un blocage, pour rester aligne
        if (ordre == "allume"){
            std::string nom;
            std::cin >> nom;
            if (!bloque && nom == "OFFSCREEN") offscreen = true;
        }
        else if (ordre == "cible"){
            long long w, h;
            std::cin >> w >> h;
            if (bloque) continue;
            if (!offscreen){
                std::cout << "CIBLE NULLE\n";
            } else {
                cibles.push_back({ w, h });
                std::cout << "CIBLE " << cibles.size() << " " << w << " " << h << "\n";
            }
        }
        else if (ordre == "vers"){
            long long k;
            std::cin >> k;
            if (bloque) continue;
            if (k == 0 || (k >= 1 && k <= static_cast<long long>(cibles.size()))){
                destination = k;
            } else {
                std::cout << "VERS REFUSE\n";
            }
        }
        else if (ordre == "taille"){
            long long w, h;
            std::cin >> w >> h;
            if (bloque) continue;
            zoneL = w;
            zoneH = h;
        }
        else if (ordre == "image"){
            if (bloque) continue;
            ++numeroImage;
            int tampon = static_cast<int>((numeroImage - 1) % F);

            // Le tampon porte encore un travail jamais termine : la boucle se fige
            if (tamponPris[tampon]){
                std::cout << "BLOQUE " << numeroImage << "\n";
                bloque = true;
                continue;
            }

            ++imagesDessinees;
            if (destination == 0){
                std::cout << "IMAGE " << numeroImage << " FENETRE\n";
            } else {
                std::cout << "IMAGE " << numeroImage << " CIBLE " << destination << "\n";
                // Zone plus large OU plus haute que la cible : le travail ne finit jamais
                const Cible& c = cibles[destination - 1];
                if (zoneL > c.largeur || zoneH > c.hauteur) tamponPris[tampon] = true;
            }
        }
    }

    std::cout << "IMAGES " << imagesDessinees << "\n";
    std::cout << "ETAT " << (bloque ? "BLOQUE" : "LIBRE") << "\n";
    return 0;
}
