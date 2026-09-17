// Chapitre 2 - Exercice 6 : Le bras en poses
//
// Bras articule a 3 segments :
//   epaule a l'origine ; coude a un bras de l'epaule ; main a un avant-bras du coude.
// Chaque articulation porte sa pose DANS LE REPERE de la precedente.
// Pose dans le monde = composer(pose_locale, pose_monde_du_parent).
//   (composer(a,b) = "appliquer a puis b" -> matrice b*a, parent a l'exterieur)
//
// On affiche coude et main dans le monde, puis on tourne l'epaule et on verifie
// que la main suit.
// Compilation : g++ -std=c++17 -O2 le_bras_en_poses.cpp -o bras

#include <cstdio>
#include <cmath>
#include <initializer_list>

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
static Quat quat_mul(Quat a, Quat b){
    return { a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
             a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x,
             a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w,
             a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z };
}
// pose equivalente a "appliquer p1 puis p2"
static Pose composer(const Pose& p1, const Pose& p2){
    return { add(rotate(p2.orientation, p1.position), p2.position),
             quat_mul(p2.orientation, p1.orientation) };
}
static Quat rotZ(double deg){
    double r = deg * M_PI / 180.0;
    return { 0.0, 0.0, std::sin(r/2), std::cos(r/2) };
}

int main(){
    const double bras = 0.30;        // longueur bras (epaule -> coude)
    const double avant_bras = 0.25;  // longueur avant-bras (coude -> main)
    const Quat id = {0,0,0,1};

    // Poses LOCALES (dans le repere du parent)
    Pose coude_local = { { bras, 0, 0 }, id };        // coude a un bras de l'epaule
    Pose main_local  = { { avant_bras, 0, 0 }, id };  // main a un avant-bras du coude

    for (double angle : { 0.0, 45.0, 90.0 }) {
        Pose epaule = { {0,0,0}, rotZ(angle) };            // epaule a l'origine, tournee
        Pose coude  = composer(coude_local, epaule);        // monde
        Pose main   = composer(main_local, coude);          // monde

        std::printf("Epaule tournee de %5.1f deg autour de Z :\n", angle);
        std::printf("   coude (monde) : %.4f %.4f %.4f\n", coude.position.x, coude.position.y, coude.position.z);
        std::printf("   main  (monde) : %.4f %.4f %.4f  (|main| = %.4f)\n",
                    main.position.x, main.position.y, main.position.z,
                    std::sqrt(main.position.x*main.position.x + main.position.y*main.position.y + main.position.z*main.position.z));
    }
    return 0;
}
