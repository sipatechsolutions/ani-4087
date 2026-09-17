// Chapitre 2 - Exercice 2 : La pose appliquee
//
// Structure Pose = position (Vec3) + quaternion (deja normalise).
// applique_pose(point) = rotation PUIS translation.
//
// Entree : 10 reels
//   position px py pz | quaternion qx qy qz qw | point x y z
// Sortie : le point transforme, 4 decimales.
//
// Compilation : g++ -std=c++17 -O2 la_pose_appliquee.cpp -o pose
// Execution   : echo "0 0 0  0 0.7071067811865476 0 0.7071067811865476  1 0 0" | ./pose

#include <cstdio>

struct Vec3 { double x, y, z; };
struct Quat { double x, y, z, w; }; // deja normalise
struct Pose { Vec3 position; Quat orientation; };

static Vec3 cross(Vec3 a, Vec3 b) {
    return { a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x };
}
static Vec3 add(Vec3 a, Vec3 b)          { return { a.x+b.x, a.y+b.y, a.z+b.z }; }
static Vec3 scale(Vec3 a, double s)      { return { a.x*s, a.y*s, a.z*s }; }

// Rotation d'un vecteur par un quaternion normalise :
// v' = v + 2w (u x v) + 2 u x (u x v)   avec u = (qx,qy,qz)
static Vec3 rotate(Quat q, Vec3 v) {
    Vec3 u = { q.x, q.y, q.z };
    Vec3 t = scale(cross(u, v), 2.0);
    return add(add(v, scale(t, q.w)), cross(u, t));
}

// Applique la pose : d'abord la rotation, puis la translation
static Vec3 applique_pose(const Pose& p, Vec3 point) {
    return add(rotate(p.orientation, point), p.position);
}

int main() {
    Pose p; Vec3 pt;
    if (std::scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
                   &p.position.x, &p.position.y, &p.position.z,
                   &p.orientation.x, &p.orientation.y, &p.orientation.z, &p.orientation.w,
                   &pt.x, &pt.y, &pt.z) != 10) {
        std::fprintf(stderr, "Entree : px py pz  qx qy qz qw  x y z\n");
        return 1;
    }
    Vec3 r = applique_pose(p, pt);
    std::printf("%.4f %.4f %.4f\n", r.x, r.y, r.z);
    return 0;
}
