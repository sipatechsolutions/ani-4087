// Chapitre 2 - Exercice 4 : L'inverse d'une pose
//
// Inverser(pose) a la main :
//   orientation inverse = conjugue du quaternion (-x,-y,-z, w)  (unitaire)
//   position    inverse = conjugue applique a (-position)
// Verification : appliquer la pose a un point, puis l'inverse au resultat,
// et afficher l'ecart au point de depart (doit etre nul aux arrondis pres).
//
// Entree : px py pz  qx qy qz qw  x y z
// Compilation : g++ -std=c++17 -O2 l_inverse_d_une_pose.cpp -o inverse

#include <cstdio>
#include <cmath>

struct Vec3 { double x, y, z; };
struct Quat { double x, y, z, w; };
struct Pose { Vec3 position; Quat orientation; };

static Vec3 cross(Vec3 a, Vec3 b){ return { a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x }; }
static Vec3 add(Vec3 a, Vec3 b){ return { a.x+b.x, a.y+b.y, a.z+b.z }; }
static Vec3 scale(Vec3 a, double s){ return { a.x*s, a.y*s, a.z*s }; }

static Vec3 rotate(Quat q, Vec3 v){
    Vec3 u = { q.x, q.y, q.z };
    Vec3 t = scale(cross(u, v), 2.0);
    return add(add(v, scale(t, q.w)), cross(u, t));
}

static Vec3 applique_pose(const Pose& p, Vec3 point){
    return add(rotate(p.orientation, point), p.position);
}

// L'inverse, ecrit a la main
static Pose inverser(const Pose& p){
    Quat conj = { -p.orientation.x, -p.orientation.y, -p.orientation.z, p.orientation.w };
    Vec3 neg_pos = { -p.position.x, -p.position.y, -p.position.z };
    Vec3 inv_pos = rotate(conj, neg_pos);
    return { inv_pos, conj };
}

int main(){
    Pose p; Vec3 pt;
    if (std::scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
                   &p.position.x,&p.position.y,&p.position.z,
                   &p.orientation.x,&p.orientation.y,&p.orientation.z,&p.orientation.w,
                   &pt.x,&pt.y,&pt.z) != 10) return 1;

    Vec3 transforme = applique_pose(p, pt);                   // pose appliquee
    Vec3 retour     = applique_pose(inverser(p), transforme); // puis l'inverse
    Vec3 ecart = { retour.x - pt.x, retour.y - pt.y, retour.z - pt.z };
    double norme = std::sqrt(ecart.x*ecart.x + ecart.y*ecart.y + ecart.z*ecart.z);

    std::printf("Point de depart : %.4f %.4f %.4f\n", pt.x, pt.y, pt.z);
    std::printf("Apres pose      : %.4f %.4f %.4f\n", transforme.x, transforme.y, transforme.z);
    std::printf("Apres inverse   : %.4f %.4f %.4f\n", retour.x, retour.y, retour.z);
    std::printf("Ecart           : %.4f %.4f %.4f  (norme %.2e)\n", ecart.x, ecart.y, ecart.z, norme);
    return 0;
}
