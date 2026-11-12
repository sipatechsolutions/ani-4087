// Chapitre 9 - Exercice 1 : declarer, et verifier
// Un handle vaut l'index de l'action plus un ; 0 est invalide.
// Une action declaree apres l'attache a un handle, mais la session ne la connait pas.
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

struct Action {
    std::string nom;
    std::string type;
    int usage;
};

int main() {
    const std::map<std::string, int> usages = {
        {"SELECT", 0},        {"GRAB", 1},           {"MENU", 2},
        {"MOVE", 3},          {"AIM_POSE", 4},       {"GRIP_POSE", 5},
        {"HAPTIC", 6},        {"SELECT_LEFT", 7},    {"GRAB_LEFT", 8},
        {"AIM_POSE_LEFT", 9}, {"GRIP_POSE_LEFT", 10},
        {"HAPTIC_LEFT", 11},  {"MOVE_RIGHT", 12}};

    std::vector<Action> actions;
    std::set<std::string> nomsVus;
    bool attache = false;
    unsigned long long k = 0;   // actions connues de la session
    int doubles = 0;

    long long n = 0;
    if (!(std::cin >> n)) n = 0;

    for (long long i = 0; i < n; ++i) {
        std::string ordre;
        if (!(std::cin >> ordre)) break;

        if (ordre == "cree") {
            Action a;
            std::string usage;
            std::cin >> a.nom >> a.type >> usage;
            auto it = usages.find(usage);
            a.usage = (it != usages.end()) ? it->second : -1;
            if (nomsVus.count(a.nom)) ++doubles;
            nomsVus.insert(a.nom);
            actions.push_back(a);
            std::cout << "ACTION " << actions.size() << ' ' << a.nom << ' '
                      << a.type << ' ' << a.usage << '\n';
        } else if (ordre == "attache") {
            if (attache) {
                std::cout << "ATTACHE REFUSE\n";
            } else {
                attache = true;
                k = actions.size();
                std::cout << "ATTACHE " << k << '\n';
            }
        } else if (ordre == "lit") {
            unsigned long long h = 0;
            std::cin >> h;
            std::cout << "LIT " << h << ' ';
            if (h == 0 || h > actions.size()) {
                std::cout << "INVALIDE\n";
            } else if (!attache || h > k) {
                std::cout << "INCONNUE\n";
            } else {
                std::cout << actions[h - 1].nom << '\n';
            }
        }
    }

    std::cout << "ACTIONS " << actions.size() << '\n';
    std::cout << "ATTACHEES " << (attache ? k : 0) << '\n';
    std::cout << "NOMS EN DOUBLE " << doubles << '\n';
    return 0;
}
