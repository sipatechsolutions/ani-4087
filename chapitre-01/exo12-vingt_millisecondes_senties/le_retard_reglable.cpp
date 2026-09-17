// Chapitre 1 - Exercice 12 : Vingt millisecondes, senties
//
// Programme sur ecran ordinaire qui suit la souris avec un RETARD REGLABLE
// (0 a 200 ms). On memorise les positions passees horodatees, puis on dessine
// le curseur a la position d'il y a "retard_ms". Touches + / - pour ajuster le
// retard, ESC pour quitter. Le retard courant est affiche dans le titre.
//
// Dependance : SDL2.
// Compilation : g++ -std=c++17 le_retard_reglable.cpp -o retard $(pkg-config --cflags --libs sdl2)
// Execution   : ./retard

#include <SDL2/SDL.h>
#include <deque>
#include <cstdio>

struct Sample { Uint32 t; int x, y; };

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* win = SDL_CreateWindow("Retard reglable",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 600, 0);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    std::deque<Sample> hist;
    int retard_ms = 0;              // reglable 0..200
    bool running = true;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_KEYDOWN) {
                SDL_Keycode k = e.key.keysym.sym;
                if (k == SDLK_ESCAPE) running = false;
                if (k == SDLK_PLUS || k == SDLK_EQUALS || k == SDLK_KP_PLUS) retard_ms += 10;
                if (k == SDLK_MINUS || k == SDLK_KP_MINUS) retard_ms -= 10;
                if (retard_ms < 0)   retard_ms = 0;
                if (retard_ms > 200) retard_ms = 200;
            }
        }

        int mx, my; SDL_GetMouseState(&mx, &my);
        Uint32 now = SDL_GetTicks();
        hist.push_back({ now, mx, my });

        // Position retardee : on remonte a l'echantillon d'il y a retard_ms
        Uint32 cible = (now > (Uint32)retard_ms) ? now - (Uint32)retard_ms : 0u;
        while (hist.size() > 1 && hist[1].t <= cible) hist.pop_front();
        int rx = hist.front().x, ry = hist.front().y;

        // Rendu
        SDL_SetRenderDrawColor(ren, 20, 20, 28, 255);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 220, 60, 60, 255);   // curseur retarde (rouge)
        SDL_Rect r = { rx - 8, ry - 8, 16, 16 };
        SDL_RenderFillRect(ren, &r);
        SDL_RenderPresent(ren);

        char titre[160];
        std::snprintf(titre, sizeof(titre),
            "Retard reglable : %d ms  (+/- pour ajuster, ESC pour quitter)", retard_ms);
        SDL_SetWindowTitle(win, titre);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
