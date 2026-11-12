// Chapitre 8 - Exercice 10 : ma salle, avec une chaine de trois images
//
// NKXRDemo ne tourne pas sur ce PC (les deux GPU, Intel HD 3000 et AMD HD 7400M,
// ne gerent pas Vulkan). Cette salle est donc ma propre boucle de rendu, la meme
// qu'a l'exercice 9 : 72 trames par seconde, deux yeux, une chaine par oeil
// avec la discipline de NkXrSwapchain. Ici chaque chaine a TROIS images, et
// chaque trame affiche l'image employee par chaque oeil.
//
// Lancement : ./salle        (30 trames)
//             ./salle 60     (nombre de trames)
// Compilation : clang++ -std=c++17 -Wall -O2 salle.cpp -o salle

#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

class Chaine {
    public:
        explicit Chaine(std::uint32_t nombreImages) : mNombre(nombreImages) {}

        bool AcquireImage(std::uint32_t& index){
            if (mEmpruntee) return false;
            index = mProchaine;
            mEmpruntee = true;
            return true;
        }

        bool ReleaseImage(){
            if (!mEmpruntee) return false;
            mProchaine = (mProchaine + 1) % mNombre;
            mEmpruntee = false;
            return true;
        }

    private:
        std::uint32_t mNombre;
        std::uint32_t mProchaine = 0;
        bool mEmpruntee = false;
};

struct Image {
    int largeur, hauteur;
    std::vector<std::uint32_t> pixels;
    Image(int l, int h) : largeur(l), hauteur(h), pixels(static_cast<size_t>(l) * h) {}
};

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
    const long long trames = (argc > 1) ? std::atoll(argv[1]) : 30;
    const int OEILS = 2;
    const std::uint32_t IMAGES = 3;
    const auto pas = std::chrono::nanoseconds(1000000000LL / 72);   // 72 Hz

    std::vector<Chaine> chaines(OEILS, Chaine(IMAGES));
    // Trois cibles par oeil : l'index emprunte choisit celle que l'on peint.
    std::vector<std::vector<Image>> cibles(OEILS, std::vector<Image>(IMAGES, Image(720, 792)));
    std::uint64_t controle = 0;

    const auto debut = std::chrono::steady_clock::now();
    auto prochaineTrame = debut;

    for (long long trame = 1; trame <= trames; ++trame){
        std::uint32_t employee[2] = {0, 0};
        for (int e = 0; e < OEILS; ++e){
            std::uint32_t index = 0;
            if (!chaines[e].AcquireImage(index)) continue;
            Dessine(cibles[e][index], trame, e);
            controle += cibles[e][index].pixels[static_cast<size_t>(trame % 997)];
            chaines[e].ReleaseImage();
            employee[e] = index;
        }
        const double ms = std::chrono::duration<double, std::milli>(
            std::chrono::steady_clock::now() - debut).count();
        std::cout << "TRAME " << trame << " GAUCHE " << employee[0]
                  << " DROIT " << employee[1] << " T " << static_cast<long long>(ms) << " ms\n";
        prochaineTrame += pas;
        std::this_thread::sleep_until(prochaineTrame);
    }
    std::cout << "CONTROLE " << (controle % 1000) << "\n";
    return 0;
}
