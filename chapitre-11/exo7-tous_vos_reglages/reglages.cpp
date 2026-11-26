// Chapitre 11 - Exercice 7 : tous vos reglages
// Classe chaque reglage selon ce que le code en fait :
//   CACHE     : un fichier lit lui-meme la variable d'environnement (GETENV) ;
//   FANTOME   : personne ne le lit ;
//   CONSTANTE : lu, mais ni l'application ni les variables ne le posent ;
//   MENU      : un champ lu et posable, qu'un menu peut donc changer.
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

int main() {
    int r = 0;
    if (!(std::cin >> r)) r = 0;

    std::vector<std::string> ordre;                    // premiere apparition
    std::map<std::string, std::set<std::string>> actions;
    for (int i = 0; i < r; ++i) {
        std::string nom, action;
        std::cin >> nom >> action;
        if (!actions.count(nom)) ordre.push_back(nom);
        actions[nom].insert(action);
    }

    int menu = 0;
    for (const std::string& nom : ordre) {
        const std::set<std::string>& a = actions[nom];
        std::string classe;
        if (a.count("GETENV")) classe = "CACHE";
        else if (!a.count("LIT")) classe = "FANTOME";
        else if (!a.count("ECRIT") && !a.count("ENV")) classe = "CONSTANTE";
        else classe = "MENU";
        if (classe == "MENU") ++menu;
        std::cout << nom << ' ' << classe << '\n';
    }
    std::cout << "MENU " << menu << " SUR " << ordre.size() << '\n';
    return 0;
}
