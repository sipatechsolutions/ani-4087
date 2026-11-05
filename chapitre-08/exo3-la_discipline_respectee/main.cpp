// Chapitre 8 - Exercice 3 : La discipline, respectee
//
// On suit les appels faits a une chaine d'echange de n images :
// acquire (emprunter), draw (dessiner), release (rendre), submit (soumettre).
// Chaque appel qui viole la discipline est refuse. La soumission envoie la
// derniere image relachee, marquee VIDE si elle a ete rendue sans dessin.
//
// Entree : n N, puis N ordres (acquire, draw, release, submit)
// Compilation : clang++ -std=c++17 -Wall main.cpp -o programme

#include <iostream>
#include <string>
#include <vector>

int main(){
    int n;
    long long N;
    if (!(std::cin >> n >> N)) return 1;

    int prochaine = 0;                    // prochaine image a emprunter
    bool empruntee = false;               // une image est-elle empruntee ?
    std::vector<bool> dessinee(n, false); // l'image a-t-elle ete dessinee pendant son dernier emprunt ?
    bool renduDepuisSoumission = false;   // une image a-t-elle ete rendue depuis la derniere soumission ?

    long long soumises = 0, refus = 0, horsEmprunt = 0;

    for (long long i = 0; i < N; ++i){
        std::string ordre;
        if (!(std::cin >> ordre)) break;

        if (ordre == "acquire"){
            if (empruntee){
                std::cout << "ACQUIRE REFUSE\n";
                ++refus;
            } else {
                empruntee = true;
                dessinee[prochaine] = false;  // nouvel emprunt : rien n'est encore dessine
                std::cout << "ACQUIRE " << prochaine << "\n";
            }
        }
        else if (ordre == "draw"){
            if (empruntee){
                dessinee[prochaine] = true;
                std::cout << "DRAW " << prochaine << "\n";
            } else {
                std::cout << "DRAW HORS EMPRUNT\n";
                ++horsEmprunt;
            }
        }
        else if (ordre == "release"){
            // Un release refuse ne fait pas avancer la prochaine image
            if (!empruntee){
                std::cout << "RELEASE REFUSE\n";
                ++refus;
            } else {
                prochaine = (prochaine + 1) % n;
                empruntee = false;
                renduDepuisSoumission = true;
                std::cout << "RELEASE OK\n";
            }
        }
        else if (ordre == "submit"){
            if (empruntee){
                std::cout << "SUBMIT REFUSE EMPRUNTEE\n";
                ++refus;
            } else if (!renduDepuisSoumission){
                std::cout << "SUBMIT REFUSE RIEN\n";
                ++refus;
            } else {
                // La derniere image relachee est celle qui precede la prochaine
                const int j = (prochaine + n - 1) % n;
                std::cout << "SUBMIT " << j << (dessinee[j] ? "" : " VIDE") << "\n";
                ++soumises;
                renduDepuisSoumission = false;
            }
        }
    }

    std::cout << "SOUMISES " << soumises << "\n";
    std::cout << "REFUS " << refus << "\n";
    std::cout << "HORS EMPRUNT " << horsEmprunt << "\n";
    return 0;
}
