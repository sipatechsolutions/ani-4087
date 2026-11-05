// Chapitre 8 - Exercice 2 : Deux chaines
//
// On cree des chaines d'echange a partir de leur description, une par oeil.
// Une chaine est refusee si sa taille est nulle (controle en premier), puis si
// son nombre d'images vaut 0 ou depasse 4. Chaque chaine acceptee reserve un
// tableau fixe de 4 emplacements, quel que soit son nombre d'images.
//
// Entree : N, puis N lignes "largeur hauteur images oeil nom" (nom = - si absent)
// Compilation : clang++ -std=c++17 -Wall main.cpp -o programme

#include <iostream>
#include <string>

static const long long EMPLACEMENTS_PAR_CHAINE = 4;
static const long long IMAGES_MAX = 4;

int main(){
    long long N;
    if (!(std::cin >> N)) return 1;

    long long acceptees = 0, occupes = 0, gauche = 0, droit = 0, sansNom = 0;

    for (long long i = 0; i < N; ++i){
        long long largeur, hauteur, images;
        int oeil;
        std::string nom;
        if (!(std::cin >> largeur >> hauteur >> images >> oeil >> nom)) break;

        const bool anonyme = (nom == "-");
        const std::string affiche = anonyme ? "SANS-NOM" : nom;

        // La taille est controlee avant le nombre d'images
        if (largeur == 0 || hauteur == 0){
            std::cout << "REFUSEE " << affiche << " TAILLE\n";
            continue;
        }
        if (images == 0 || images > IMAGES_MAX){
            std::cout << "REFUSEE " << affiche << " IMAGES\n";
            continue;
        }

        std::cout << "CHAINE " << affiche << " " << largeur << " " << hauteur << " "
                  << images << " " << (oeil == 0 ? "GAUCHE" : "DROIT") << "\n";

        // Le bilan ne compte que les chaines acceptees
        ++acceptees;
        occupes += images;
        if (oeil == 0) ++gauche; else ++droit;
        if (anonyme) ++sansNom;
    }

    std::cout << "ACCEPTEES " << acceptees << "\n";
    std::cout << "EMPLACEMENTS " << acceptees * EMPLACEMENTS_PAR_CHAINE << "\n";
    std::cout << "OCCUPES " << occupes << "\n";
    std::cout << "GAUCHE " << gauche << "\n";
    std::cout << "DROIT " << droit << "\n";
    std::cout << "SANS NOM " << sansNom << "\n";
    return 0;
}
