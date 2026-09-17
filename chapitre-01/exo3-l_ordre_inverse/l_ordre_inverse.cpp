// Chapitre 2 - Exercice 3 : L'ordre inverse
//
// Deux facons d'appliquer une pose a un point :
//   RT : rotation PUIS translation   ->  R*p + t   (l'ordre correct)
//   TR : translation PUIS rotation   ->  R*(p + t) = R*p + R*t
// On affiche les deux resultats pour le meme point.
// Ils coincident si et seulement si R*t = t (t invariant par la rotation).
//
// Entree : px py pz  qx qy qz qw  x y z
// Compilation : g++ -std=c++17 -O2 l_ordre_inverse.cpp -o ordre

#include <cstdio>

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

// Ordre correct : rotation puis translation
static Vec3 applique_RT(const Pose& p, Vec3 point){
    return add(rotate(p.orientation, point), p.position);
}
// Ordre inverse : translation puis rotation
static Vec3 applique_TR(const Pose& p, Vec3 point){
    return rotate(p.orientation, add(point, p.position));
}

int main(){
    Pose p; Vec3 pt;
    if (std::scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
                   &p.position.x,&p.position.y,&p.position.z,
                   &p.orientation.x,&p.orientation.y,&p.orientation.z,&p.orientation.w,
                   &pt.x,&pt.y,&pt.z) != 10) return 1;
    Vec3 rt = applique_RT(p, pt);
    Vec3 tr = applique_TR(p, pt);
    std::printf("Rotation puis translation : %.4f %.4f %.4f\n", rt.x, rt.y, rt.z);
    std::printf("Translation puis rotation : %.4f %.4f %.4f\n", tr.x, tr.y, tr.z);
    return 0;
}
