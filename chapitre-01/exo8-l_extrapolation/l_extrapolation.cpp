// Chapitre 2 - Exercice 8 : L'extrapolation
//
// Avance une pose de dt secondes a vitesses constantes :
//   position    : p + v_lin * dt
//   orientation : delta * q, ou delta est la rotation par la vitesse angulaire
//                 w (axe*rad/s) pendant dt : angle = |w|*dt, axe = w/|w|.
// Cas |w| ~ 0 : delta = identite (aucune division par zero).
//
// Entree : px py pz  qx qy qz qw  vx vy vz  wx wy wz  dt   (14 reels)
// Compilation : g++ -std=c++17 -O2 l_extrapolation.cpp -o extrapo

#include <cstdio>
#include <cmath>

struct Vec3 { double x, y, z; };
struct Quat { double x, y, z, w; };
struct Pose { Vec3 position; Quat orientation; };

static Quat quat_mul(Quat a, Quat b){
    return { a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
             a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x,
             a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w,
             a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z };
}
static Quat normalise(Quat q){
    double n = std::sqrt(q.x*q.x+q.y*q.y+q.z*q.z+q.w*q.w);
    if(n < 1e-15) return {0,0,0,1};
    return { q.x/n, q.y/n, q.z/n, q.w/n };
}

// Avance la pose de dt a vitesses constantes v_lin et w (angulaire, rad/s)
static Pose avancer(const Pose& p, Vec3 v_lin, Vec3 w, double dt){
    Pose r;
    // Position : integration lineaire
    r.position = { p.position.x + v_lin.x*dt,
                   p.position.y + v_lin.y*dt,
                   p.position.z + v_lin.z*dt };
    // Orientation : rotation delta par la vitesse angulaire
    double vitesse = std::sqrt(w.x*w.x + w.y*w.y + w.z*w.z); // |w| en rad/s
    double angle = vitesse * dt;                              // angle total
    Quat delta;
    if(vitesse < 1e-12){
        delta = {0,0,0,1};        // vitesse angulaire nulle -> pas de rotation (pas de /0)
    } else {
        double s = std::sin(angle/2.0) / vitesse; // = sin(angle/2) * (1/|w|) : axe normalise
        delta = { w.x*s, w.y*s, w.z*s, std::cos(angle/2.0) };
    }
    r.orientation = normalise(quat_mul(delta, p.orientation));
    return r;
}

int main(){
    Pose p; Vec3 v, w; double dt;
    if(std::scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
        &p.position.x,&p.position.y,&p.position.z,
        &p.orientation.x,&p.orientation.y,&p.orientation.z,&p.orientation.w,
        &v.x,&v.y,&v.z, &w.x,&w.y,&w.z, &dt) != 14) return 1;

    Pose e = avancer(p, v, w, dt);
    std::printf("position   : %.4f %.4f %.4f\n", e.position.x, e.position.y, e.position.z);
    std::printf("quaternion : %.4f %.4f %.4f %.4f\n",
                e.orientation.x, e.orientation.y, e.orientation.z, e.orientation.w);
    return 0;
}
