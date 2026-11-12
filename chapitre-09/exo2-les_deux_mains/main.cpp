// Chapitre 9 - Exercice 2 : les deux mains
// Chaque main a ses propres commandes dans le simulateur ;
// le deplacement se fait aux fleches, ZQSDWA pilotent la tete.
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

struct Liaison {
    std::string main;
    std::string commande;
};

struct Action {
    std::string nom;
    Liaison liaison;
};

// Manche a deux axes : droite / gauche / haut / bas.
static std::string manche(const std::set<std::string>& tenues,
                          const std::string& droite, const std::string& gauche,
                          const std::string& haut, const std::string& bas) {
    int x = (tenues.count(droite) ? 1 : 0) - (tenues.count(gauche) ? 1 : 0);
    int y = (tenues.count(haut) ? 1 : 0) - (tenues.count(bas) ? 1 : 0);
    return std::to_string(x) + "," + std::to_string(y);
}

int main() {
    const std::map<std::string, Liaison> table = {
        {"SELECT", {"DROITE", "SOURIS_G"}},
        {"GRAB", {"DROITE", "SOURIS_D"}},
        {"MENU", {"GAUCHE", "TAB"}},
        {"MOVE", {"GAUCHE", "FLECHES"}},
        {"AIM_POSE", {"DROITE", "AUCUNE"}},
        {"GRIP_POSE", {"DROITE", "AUCUNE"}},
        {"HAPTIC", {"DROITE", "AUCUNE"}},
        {"SELECT_LEFT", {"GAUCHE", "SOURIS_M"}},
        {"GRAB_LEFT", {"GAUCHE", "MAJ_G"}},
        {"AIM_POSE_LEFT", {"GAUCHE", "AUCUNE"}},
        {"GRIP_POSE_LEFT", {"GAUCHE", "AUCUNE"}},
        {"HAPTIC_LEFT", {"GAUCHE", "AUCUNE"}},
        {"MOVE_RIGHT", {"DROITE", "IJKL"}}};
    const std::set<std::string> touchesTete = {"Z", "Q", "S", "D", "W", "A"};

    long long a = 0, t = 0;
    if (!(std::cin >> a >> t)) return 0;

    std::vector<Action> actions;
    int droite = 0, gauche = 0;
    for (long long i = 0; i < a; ++i) {
        Action act;
        std::string usage;
        std::cin >> act.nom >> usage;
        auto it = table.find(usage);
        act.liaison = (it != table.end()) ? it->second : Liaison{"DROITE", "AUCUNE"};
        if (act.liaison.main == "DROITE") ++droite; else ++gauche;
        actions.push_back(act);
        std::cout << act.nom << ' ' << act.liaison.main << ' '
                  << act.liaison.commande << '\n';
    }

    int tete = 0;
    for (long long image = 1; image <= t; ++image) {
        int k = 0;
        std::cin >> k;
        std::set<std::string> tenues;
        bool teteBouge = false;
        for (int j = 0; j < k; ++j) {
            std::string c;
            std::cin >> c;
            tenues.insert(c);
            if (touchesTete.count(c)) teteBouge = true;
        }
        if (teteBouge) ++tete;

        std::cout << image;
        for (const Action& act : actions) {
            const std::string& cmd = act.liaison.commande;
            std::cout << ' ';
            if (cmd == "AUCUNE") {
                std::cout << '-';
            } else if (cmd == "FLECHES") {
                std::cout << manche(tenues, "F_DROITE", "F_GAUCHE", "F_HAUT", "F_BAS");
            } else if (cmd == "IJKL") {
                std::cout << manche(tenues, "L", "J", "I", "K");
            } else {
                std::cout << (tenues.count(cmd) ? 1 : 0);
            }
        }
        std::cout << '\n';
    }

    std::cout << "DROITE " << droite << '\n';
    std::cout << "GAUCHE " << gauche << '\n';
    std::cout << "TETE " << tete << '\n';
    return 0;
}
