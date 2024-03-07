#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
    // SDL inicializálása
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Nem sikerult inicializalni az SDL-t: %s\n", SDL_GetError());
        return 1;
    }

    // Az ablak létrehozása
    SDL_Window* window = SDL_CreateWindow("Eger pozicio", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Nem sikerult az ablak letrehozasa: %s\n", SDL_GetError());
        return 1;
    }

    // Az esemény kezelésére szolgáló változó
    SDL_Event event;

    // Fő ciklus
    while (1) {
        // Események kezelése
        while (SDL_PollEvent(&event) != 0) {
            // Kilépés, ha bezárjuk az ablakot
            if (event.type == SDL_QUIT) {
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 0;
            }
            // Egérmozgás esemény kezelése
            else if (event.type == SDL_MOUSEMOTION) {
                int mouseX, mouseY;
                // Egérkurzor pozíciójának lekérdezése
                SDL_GetMouseState(&mouseX, &mouseY);
                printf("Eger pozicio: X = %d, Y = %d\n", mouseX, mouseY);
            }
        }
    }

    return 0;
}