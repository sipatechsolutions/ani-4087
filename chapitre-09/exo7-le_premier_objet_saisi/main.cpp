// Chapitre 9 - Exercice 7 : le premier objet saisi
// A la saisie, une fois : attache = inverse(paume) * objet.
// A chaque image ensuite : objet = paume * attache.
// L'objet reste ainsi tenu la ou on l'a pris, au lieu de sauter dans la main.
#include <iostream>
#include <vector>

struct Pose {
    long long x = 0;
    long long y = 0;
    int k = 0;   // quarts de tour, sens inverse des aiguilles d'une montre
};

static int normaliser(int k) { return ((k % 4) + 4) % 4; }

// Tourne le vecteur (u, v) de k quarts de tour.
static void tourner(long long u, long long v, int k, long long& rx, long long& ry) {
    switch (normaliser(k)) {
        case 0: rx = u;  ry = v;  break;
        case 1: rx = -v; ry = u;  break;
        case 2: rx = -u; ry = -v; break;
        default: rx = v; ry = -u; break;
    }
}

// A * B : B exprimee dans le repere de A.
static Pose composer(const Pose& a, const Pose& b) {
    long long rx = 0, ry = 0;
    tourner(b.x, b.y, a.k, rx, ry);
    Pose r;
    r.x = a.x + rx;
    r.y = a.y + ry;
    r.k = normaliser(a.k + b.k);
    return r;
}

static Pose inverser(const Pose& a) {
    Pose r;
    r.k = normaliser(4 - a.k);
    tourner(-a.x, -a.y, r.k, r.x, r.y);
    return r;
}

int main() {
    long long m = 0, t = 0;
    if (!(std::cin >> m >> t)) return 0;

    std::vector<Pose> objets(m > 0 ? m : 0);
    for (Pose& o : objets) {
        std::cin >> o.x >> o.y >> o.k;
        o.k = normaliser(o.k);
    }

    int bPrecedent = 0;
    long long tenu = -1;    // index de l'objet tenu, -1 si aucun
    Pose attache;
    long long saisies = 0, ratees = 0;

    for (long long image = 1; image <= t; ++image) {
        Pose paume;
        int b = 0;
        std::cin >> paume.x >> paume.y >> paume.k >> b;
        paume.k = normaliser(paume.k);

        bool appui = b == 1 && bPrecedent == 0;
        bool relache = b == 0 && bPrecedent == 1;
        bPrecedent = b;
        bool rate = false;

        if (appui) {
            long long meilleur = -1;
            long long meilleureDistance = 0;
            for (long long j = 0; j < static_cast<long long>(objets.size()); ++j) {
                long long dx = objets[j].x - paume.x;
                long long dy = objets[j].y - paume.y;
                long long d2 = dx * dx + dy * dy;
                if (d2 <= 22500 && (meilleur < 0 || d2 < meilleureDistance)) {
                    meilleur = j;
                    meilleureDistance = d2;
                }
            }
            if (meilleur >= 0) {
                tenu = meilleur;
                attache = composer(inverser(paume), objets[tenu]);
                ++saisies;
            } else {
                rate = true;
                ++ratees;
            }
        } else if (relache) {
            tenu = -1;      // l'objet reste ou il est
        }

        if (tenu >= 0) {
            objets[tenu] = composer(paume, attache);
            const Pose& o = objets[tenu];
            std::cout << image << " TIENT " << (tenu + 1) << ' ' << o.x << ' '
                      << o.y << ' ' << o.k << '\n';
        } else if (rate) {
            std::cout << image << " RATE\n";
        } else {
            std::cout << image << " LIBRE\n";
        }
    }

    std::cout << "SAISIES " << saisies << '\n';
    std::cout << "RATEES " << ratees << '\n';
    for (std::size_t j = 0; j < objets.size(); ++j) {
        std::cout << "OBJET " << (j + 1) << ' ' << objets[j].x << ' '
                  << objets[j].y << ' ' << objets[j].k << '\n';
    }
    return 0;
}
