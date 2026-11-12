// Chapitre 9 - Exercice 9 : une intention, deux commandes
// Les actions sont declarees une seule fois, par leur usage.
// La table de correspondance usage -> commande est une donnee lue a part :
// changer de materiel ne change qu'elle, jamais le reste du code.
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

struct Action {
    std::string nom;
    std::string usage;
};

// La table : le seul endroit qui connait les commandes du materiel.
using Table = std::map<std::string, std::string>;

static Table lireTable() {
    Table table;
    int u = 0;
    std::cin >> u;
    for (int i = 0; i < u; ++i) {
        std::string usage, commande;
        std::cin >> usage >> commande;
        table[usage] = commande;
    }
    return table;
}

// Rejoue les images avec une table ; renvoie les lignes d'images produites.
static std::vector<std::string> rejouer(const std::vector<Action>& actions,
                                        const Table& table) {
    std::vector<bool> appuyee(actions.size(), false);
    std::vector<std::string> lignes;

    int t = 0;
    std::cin >> t;
    for (int image = 1; image <= t; ++image) {
        int k = 0;
        std::cin >> k;
        std::set<std::string> tenues;
        for (int j = 0; j < k; ++j) {
            std::string c;
            std::cin >> c;
            tenues.insert(c);
        }

        std::string ligne = std::to_string(image);
        bool aucune = true;
        for (std::size_t a = 0; a < actions.size(); ++a) {
            auto it = table.find(actions[a].usage);
            bool maintenant = it != table.end() && tenues.count(it->second) > 0;
            if (maintenant && !appuyee[a]) {
                ligne += ' ' + actions[a].nom;
                aucune = false;
            }
            appuyee[a] = maintenant;
        }
        if (aucune) ligne += " -";
        lignes.push_back(ligne);
    }
    return lignes;
}

int main() {
    int a = 0;
    if (!(std::cin >> a)) return 0;
    std::vector<Action> actions(a);
    for (Action& act : actions) std::cin >> act.nom >> act.usage;

    std::vector<std::vector<std::string>> resultats;
    for (int i = 1; i <= 2; ++i) {
        Table table = lireTable();
        std::cout << "TABLE " << i << '\n';
        for (const Action& act : actions) {
            if (table.find(act.usage) == table.end()) {
                std::cout << "INACTIVE " << act.nom << '\n';
            }
        }
        std::vector<std::string> lignes = rejouer(actions, table);
        for (const std::string& l : lignes) std::cout << l << '\n';
        resultats.push_back(lignes);
    }

    std::cout << "IDENTIQUES " << (resultats[0] == resultats[1] ? "OUI" : "NON")
              << '\n';
    return 0;
}
