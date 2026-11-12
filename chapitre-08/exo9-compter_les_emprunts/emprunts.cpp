// Chapitre 8 - Exercice 9 : Compter les emprunts
//
// On compte les emprunts reussis, les emprunts refuses et les liberations d'une
// boucle de rendu. Chaque emprunt reussi doit finir par une liberation : un seul
// chemin qui l'oublie (sortie) fige la chaine, et toutes les trames suivantes
// sont refusees. A tout instant : reussies - liberations = 1 si une image est
// encore empruntee, 0 sinon.
//
// Entree : n N, puis N mots (normal, sortie, double)
// Compilation : clang++ -std=c++17 -Wall emprunts.cpp -o emprunts

#include <iostream>
#include <string>

struct Chaine {
    long long nombreImages;
    long long prochaine = 0;
    bool empruntee = false;

    long long reussies = 0, refusees = 0, liberations = 0;

    bool AcquireImage(){
        if (empruntee){ ++refusees; return false; }
        empruntee = true;
        ++reussies;
        return true;
    }

    bool ReleaseImage(){
        if (!empruntee) return false;
        prochaine = (prochaine + 1) % nombreImages;
        empruntee = false;
        ++liberations;
        return true;
    }
};

int main(){
    long long n, N;
    if (!(std::cin >> n >> N)) return 1;

    Chaine chaine{ n };
    long long premiereFuite = 0;   // 0 : aucune fuite

    for (long long t = 1; t <= N; ++t){
        std::string chemin;
        if (!(std::cin >> chemin)) break;

        // Chaque trame commence par un emprunt ; refuse, elle s'arrete la
        if (!chaine.AcquireImage()){
            std::cout << t << " BLOQUEE\n";
            continue;
        }

        if (chemin == "normal"){
            // dessin, puis liberation
            chaine.ReleaseImage();
            std::cout << t << " OK\n";
        }
        else if (chemin == "sortie"){
            // sortie anticipee : l'image n'est jamais rendue
            std::cout << t << " FUITE\n";
            if (premiereFuite == 0) premiereFuite = t;
        }
        else if (chemin == "double"){
            chaine.AcquireImage();     // second emprunt, refuse et compte
            chaine.ReleaseImage();
            std::cout << t << " DOUBLE\n";
        }
    }

    std::cout << "REUSSIES " << chaine.reussies << "\n";
    std::cout << "REFUSEES " << chaine.refusees << "\n";
    std::cout << "LIBERATIONS " << chaine.liberations << "\n";
    std::cout << "ECART " << chaine.reussies - chaine.liberations << "\n";
    if (premiereFuite == 0) std::cout << "PREMIERE FUITE AUCUNE\n";
    else std::cout << "PREMIERE FUITE " << premiereFuite << "\n";
    return 0;
}
