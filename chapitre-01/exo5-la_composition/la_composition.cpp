// Chapitre 2 - Exercice 5 : La composition de deux poses
//
// composer(p1, p2) = la pose equivalente a "appliquer p1 PUIS p2".
//   appliquer p1 puis p2 a un point :
//     p'  = R1*p + t1
//     p'' = R2*p' + t2 = (R2*R1)*p + (R2*t1 + t2)
//   donc :  orientation = q2 * q1 ,  position = R2*t1 + t2
//
// Verification : composer puis appliquer == appliquer p1 puis p2.
// Entree : pos1(3) quat1(4) pos2(3) quat2(4) point(3)  = 17 reels
// Compilation : g++ -std=c++17 -O2 la_composition.cpp -o compo

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

// Produit de Hamilton a*b
static Quat quat_mul(Quat a, Quat b){
    return {
        a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
        a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x,
        a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w,
        a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z
    };
}

// Pose equivalente a "appliquer p1 puis p2"
static Pose composer(const Pose& p1, const Pose& p2){
    Quat q = quat_mul(p2.orientation, p1.orientation);              // R2*R1
    Vec3 t = add(rotate(p2.orientation, p1.position), p2.position); // R2*t1 + t2
    return { t, q };
}

int main(){
    Pose p1, p2; Vec3 pt;
    if (std::scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
        &p1.position.x,&p1.position.y,&p1.position.z,
        &p1.orientation.x,&p1.orientation.y,&p1.orientation.z,&p1.orientation.w,
        &p2.position.x,&p2.position.y,&p2.position.z,
        &p2.orientation.x,&p2.orientation.y,&p2.orientation.z,&p2.orientation.w,
        &pt.x,&pt.y,&pt.z) != 17) return 1;

    // Chemin 1 : appliquer l'une apres l'autre
    Vec3 apres_p1 = applique_pose(p1, pt);
    Vec3 successif = applique_pose(p2, apres_p1);

    // Chemin 2 : composer puis appliquer
    Vec3 compose = applique_pose(composer(p1, p2), pt);

    Vec3 ecart = { compose.x - successif.x, compose.y - successif.y, compose.z - successif.z };
    double norme = std::sqrt(ecart.x*ecart.x + ecart.y*ecart.y + ecart.z*ecart.z);

    std::printf("Applique p1 puis p2 : %.4f %.4f %.4f\n", successif.x, successif.y, successif.z);
    std::printf("Compose puis applique: %.4f %.4f %.4f\n", compose.x, compose.y, compose.z);
    std::printf("Ecart                : %.4f %.4f %.4f  (norme %.2e)\n", ecart.x, ecart.y, ecart.z, norme);
    return 0;
}
