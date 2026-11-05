// Chapitre 8 - Exercice 7 : L'ecran noir, provoque
//
// On suit la cible, la chaine et les images d'un oeil. Apres un
// redimensionnement, la chaine neuve est vide : le rendu reste juste, mais le
// compositeur recoit 0 et l'ecran devient noir, jusqu'au prochain enregistre.
// Si l'on garde l'ancienne chaine, elle soumet une ancienne cible : PERIMEE.
//
// Entree : N, puis N ordres (cible w h, chaine, enregistre, image)
// Compilation : clang++ -std=c++17 -Wall main.cpp -o programme

#include <iostream>
#include <string>

static const long long PREMIERE_POIGNEE = 101;

int main(){
    long long N;
    if (!(std::cin >> N)) return 1;

    long long prochainePoignee = PREMIERE_POIGNEE;
    long long poigneeCourante = 0;   // 0 avant la premiere cible
    long long index0 = 0;            // ce que la chaine a range a l'index 0
    long long numeroImage = 0;
    long long affichees = 0, noires = 0, perimees = 0;

    for (long long i = 0; i < N; ++i){
        std::string ordre;
        if (!(std::cin >> ordre)) break;

        if (ordre == "cible"){
            long long w, h;
            std::cin >> w >> h;
            poigneeCourante = prochainePoignee++;
            std::cout << "CIBLE " << poigneeCourante << " " << w << " " << h << "\n";
        }
        else if (ordre == "chaine"){
            index0 = 0;                  // chaine neuve : rien n'est range
        }
        else if (ordre == "enregistre"){
            index0 = poigneeCourante;    // SetImageNative(0, poignee courante)
        }
        else if (ordre == "image"){
            ++numeroImage;
            // Le rendu dessine toujours juste : tout depend de ce qui est range
            if (index0 == 0){
                std::cout << "IMAGE " << numeroImage << " NOIR\n";
                ++noires;
            } else if (index0 == poigneeCourante){
                std::cout << "IMAGE " << numeroImage << " AFFICHE " << index0 << "\n";
                ++affichees;
            } else {
                std::cout << "IMAGE " << numeroImage << " PERIMEE " << index0 << "\n";
                ++perimees;
            }
        }
    }

    std::cout << "AFFICHEES " << affichees << "\n";
    std::cout << "NOIRES " << noires << "\n";
    std::cout << "PERIMEES " << perimees << "\n";
    return 0;
}
