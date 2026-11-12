// Chapitre 8 - Exercice 9 : ma boucle de rendu, instrumentee
//
// Une boucle de rendu reelle, cadencee a 72 trames par seconde comme un casque,
// qui dessine deux yeux dans deux images en memoire (une chaine d'une image par
// oeil, comme le simulateur de NKXR). La chaine reprend la discipline de
// NkXrSwapchain : double emprunt refuse, liberation exigee.
// Elle compte les emprunts reussis, refuses et les liberations pendant 60 s.
//
// Lancement : ./boucle            (60 secondes)
//             ./boucle 10         (duree en secondes)
// Compilation : clang++ -std=c++17 -Wall -O2 boucle.cpp -o boucle

#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

// Meme discipline que nkentseu::xr::NkXrSwapchain, avec les trois compteurs
class Chaine {
    public:
        explicit Chaine(std::uint32_t nombreImages) : mNombre(nombreImages) {}

        bool AcquireImage(std::uint32_t& index){
            if (mEmpruntee){ ++refusees; return false; }
            index = mProchaine;
            mEmpruntee = true;
            ++reussies;
            return true;
        }

        bool ReleaseImage(){
            if (!mEmpruntee) return false;
            mProchaine = (mProchaine + 1) % mNombre;
            mEmpruntee = false;
            ++liberations;
            return true;
        }

        bool IsAcquired() const { return mEmpruntee; }

        long long reussies = 0, refusees = 0, liberations = 0;

    private:
        std::uint32_t mNombre;
        std::uint32_t mProchaine = 0;
        bool mEmpruntee = false;
};

// Une cible de rendu en memoire : on y dessine vraiment chaque pixel
struct Image {
    int largeur, hauteur;
    std::vector<std::uint32_t> pixels;
    Image(int l, int h) : largeur(l), hauteur(h), pixels(static_cast<size_t>(l) * h) {}
};

// Fond en degrade + un carre qui avance : de quoi occuper la trame
static void Dessine(Image& img, long long trame, int oeil){
    const int cote = img.largeur / 8;
    const int x0 = static_cast<int>((trame * 4 + oeil * 12) % (img.largeur - cote));
    const int y0 = img.hauteur / 2 - cote / 2;
    for (int y = 0; y < img.hauteur; ++y){
        for (int x = 0; x < img.largeur; ++x){
            std::uint32_t c = 0xFF000000u | (static_cast<std::uint32_t>(x * 255 / img.largeur) << 16)
                            | (static_cast<std::uint32_t>(y * 255 / img.hauteur) << 8);
            if (x >= x0 && x < x0 + cote && y >= y0 && y < y0 + cote) c = 0xFFFFFFFFu;
            img.pixels[static_cast<size_t>(y) * img.largeur + x] = c;
        }
    }
}

int main(int argc, char** argv){
    const int duree = (argc > 1) ? std::atoi(argv[1]) : 60;
    const int OEILS = 2;
    const auto pas = std::chrono::nanoseconds(1000000000LL / 72);   // 72 Hz

    std::vector<Chaine> chaines(OEILS, Chaine(1));
    std::vector<Image> cibles(OEILS, Image(720, 792));
    std::uint64_t controle = 0;   // empeche le compilateur d'effacer le dessin

    const auto debut = std::chrono::steady_clock::now();
    auto prochaineTrame = debut;
    long long trame = 0;

    while (std::chrono::steady_clock::now() - debut < std::chrono::seconds(duree)){
        ++trame;
        for (int e = 0; e < OEILS; ++e){
            std::uint32_t index = 0;
            if (!chaines[e].AcquireImage(index)) continue;   // emprunt refuse : rien a rendre

            // CHEMIN QUI FUIRAIT : une sortie anticipee placee ici, par exemple
            //     if (fenetreReduite) continue;
            // quitte l'oeil apres l'emprunt sans ReleaseImage. A la trame
            // suivante, AcquireImage est refuse pour toujours sur cet oeil.

            Dessine(cibles[e], trame, e);
            controle += cibles[e].pixels[static_cast<size_t>(trame % 997)];

            chaines[e].ReleaseImage();
        }
        prochaineTrame += pas;
        std::this_thread::sleep_until(prochaineTrame);
    }

    const double secondes = std::chrono::duration<double>(std::chrono::steady_clock::now() - debut).count();
    long long reussies = 0, refusees = 0, liberations = 0;
    bool encoreEmpruntee = false;
    for (const Chaine& c : chaines){
        reussies += c.reussies;
        refusees += c.refusees;
        liberations += c.liberations;
        encoreEmpruntee = encoreEmpruntee || c.IsAcquired();
    }

    std::cout << "DUREE " << secondes << " s\n";
    std::cout << "TRAMES " << trame << "\n";
    std::cout << "REUSSIES " << reussies << "\n";
    std::cout << "REFUSEES " << refusees << "\n";
    std::cout << "LIBERATIONS " << liberations << "\n";
    std::cout << "ECART " << reussies - liberations << "\n";
    std::cout << "ENCORE EMPRUNTEE " << (encoreEmpruntee ? "OUI" : "NON") << "\n";
    std::cout << "CONTROLE " << (controle % 1000) << "\n";
    return 0;
}
