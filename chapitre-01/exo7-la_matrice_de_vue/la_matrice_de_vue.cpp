// Chapitre 2 - Exercice 7 : La matrice de vue (deux inverses)
//
// Version A : inverse la matrice 4x4 de la pose par une inversion GENERALE
//             (Gauss-Jordan). Sur une matrice singuliere, elle rend
//             SILENCIEUSEMENT l'identite au lieu d'echouer.
// Version B : construit directement l'inverse : conjugue du quaternion
//             (rotation transposee) et translation opposee -R^T t.
//
// On compare les 16 coefficients pour une pose valide.
// Puis on passe une pose DEGENEREE (quaternion nul) a la version A.
//
// Compilation : g++ -std=c++17 -O2 la_matrice_de_vue.cpp -o vue

#include <cstdio>
#include <cmath>
#include <utility>

struct Vec3 { double x, y, z; };
struct Quat { double x, y, z, w; };
struct Pose { Vec3 position; Quat orientation; };
struct Mat4 { double m[16]; }; // row-major : m[ligne*4 + colonne]

static Mat4 identite(){
    Mat4 r{}; for(int i=0;i<4;i++) r.m[i*4+i]=1.0; return r;
}

// Matrice d'une pose : rotation (formule quaternion, valable non normalise) + translation
static Mat4 mat_from_pose(const Pose& p){
    double x=p.orientation.x, y=p.orientation.y, z=p.orientation.z, w=p.orientation.w;
    Mat4 M{};
    M.m[0]=w*w+x*x-y*y-z*z; M.m[1]=2*(x*y-w*z);     M.m[2]=2*(x*z+w*y);     M.m[3]=p.position.x;
    M.m[4]=2*(x*y+w*z);     M.m[5]=w*w-x*x+y*y-z*z; M.m[6]=2*(y*z-w*x);     M.m[7]=p.position.y;
    M.m[8]=2*(x*z-w*y);     M.m[9]=2*(y*z+w*x);     M.m[10]=w*w-x*x-y*y+z*z;M.m[11]=p.position.z;
    M.m[12]=0; M.m[13]=0; M.m[14]=0; M.m[15]=1;
    return M;
}

// Version A : inversion GENERALE (Gauss-Jordan). Retourne l'identite en silence si singuliere.
static Mat4 inverse_generale(const Mat4& in){
    double a[4][8];
    for(int i=0;i<4;i++){ for(int j=0;j<4;j++){ a[i][j]=in.m[i*4+j]; a[i][j+4]=(i==j)?1.0:0.0; } }
    for(int col=0; col<4; col++){
        int piv=col; double best=std::fabs(a[col][col]);
        for(int r=col+1;r<4;r++){ if(std::fabs(a[r][col])>best){ best=std::fabs(a[r][col]); piv=r; } }
        if(best < 1e-12){
            // matrice singuliere : au lieu d'echouer, on rend l'identite (piege !)
            return identite();
        }
        for(int j=0;j<8;j++) std::swap(a[col][j], a[piv][j]);
        double d=a[col][col];
        for(int j=0;j<8;j++) a[col][j]/=d;
        for(int r=0;r<4;r++){ if(r==col) continue; double f=a[r][col];
            for(int j=0;j<8;j++) a[r][j]-=f*a[col][j]; }
    }
    Mat4 out{};
    for(int i=0;i<4;i++) for(int j=0;j<4;j++) out.m[i*4+j]=a[i][j+4];
    return out;
}

// Version B : inverse analytique = R^T et -R^T t
static Mat4 inverse_analytique(const Pose& p){
    Mat4 M = mat_from_pose(p); // pour recuperer R
    Mat4 inv{};
    // rotation transposee
    for(int i=0;i<3;i++) for(int j=0;j<3;j++) inv.m[i*4+j]=M.m[j*4+i];
    // translation : -R^T * t
    double tx=p.position.x, ty=p.position.y, tz=p.position.z;
    inv.m[3]  = -(M.m[0]*tx + M.m[4]*ty + M.m[8]*tz);
    inv.m[7]  = -(M.m[1]*tx + M.m[5]*ty + M.m[9]*tz);
    inv.m[11] = -(M.m[2]*tx + M.m[6]*ty + M.m[10]*tz);
    inv.m[15] = 1.0;
    return inv;
}

static void afficher(const char* titre, const Mat4& M){
    std::printf("%s\n", titre);
    for(int i=0;i<4;i++)
        std::printf("  % .4f % .4f % .4f % .4f\n", M.m[i*4], M.m[i*4+1], M.m[i*4+2], M.m[i*4+3]);
}

int main(){
    // Pose valide : translation (5,-2,3), quaternion normalise
    Pose p = { {5,-2,3}, {0.1,0.2,0.3,0.9273618495495700} };

    Mat4 invA = inverse_generale(mat_from_pose(p));
    Mat4 invB = inverse_analytique(p);

    double maxdiff=0;
    for(int i=0;i<16;i++) maxdiff = std::fmax(maxdiff, std::fabs(invA.m[i]-invB.m[i]));

    afficher("Version A (inversion generale) :", invA);
    afficher("Version B (conjugue + translation opposee) :", invB);
    std::printf("Ecart max sur les 16 coefficients : %.2e\n\n", maxdiff);

    // Pose DEGENEREE : quaternion nul -> bloc rotation nul -> matrice singuliere
    Pose deg = { {5,-2,3}, {0,0,0,0} };
    Mat4 Mdeg = mat_from_pose(deg);
    afficher("Matrice de la pose degeneree (singuliere) :", Mdeg);
    Mat4 invDeg = inverse_generale(Mdeg);
    afficher("Version A appliquee a la pose degeneree -> rend :", invDeg);
    return 0;
}
