#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAX_LINE_COUNT 100

typedef struct {
    int x1, y1; // Kezdőpont koordinátái
    int x2, y2; // Végpont koordinátái
} Line;

int main(int argc, char* argv[]) {
    // SDL inicializálása
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Nem sikerült inicializálni az SDL-t: %s\n", SDL_GetError());
        return 1;
    }

    // Ablak létrehozása
    SDL_Window* window = SDL_CreateWindow("Szakasz rajzoló", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Nem sikerült az ablak létrehozása: %s\n", SDL_GetError());
        return 1;
    }

    // Renderer létrehozása
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Nem sikerült a renderer létrehozása: %s\n", SDL_GetError());
        return 1;
    }

    // Szakaszok tömbje
    Line lines[MAX_LINE_COUNT];
    int lineCount = 0;

    // Az eseménykezelő változó
    SDL_Event event;

    // Fő ciklus
    int quit = 0;
    while (!quit) {
        // Események kezelése
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                // Egér bal gomb lenyomás eseménye
                if (lineCount < MAX_LINE_COUNT) {
                    // Szakasz hozzáadása a tömbhöz
                    lines[lineCount].x1 = event.button.x;
                    lines[lineCount].y1 = event.button.y;
                    lines[lineCount].x2 = event.button.x;
                    lines[lineCount].y2 = event.button.y;
                    lineCount++;
                }
            } else if (event.type == SDL_MOUSEMOTION && (event.motion.state & SDL_BUTTON(SDL_BUTTON_LEFT))) {
                // Egérmozgás eseménye bal gomb lenyomva
                if (lineCount > 0) {
                    // Utolsó szakasz végpontjának frissítése
                    lines[lineCount - 1].x2 = event.motion.x;
                    lines[lineCount - 1].y2 = event.motion.y;
                }
            }
        }

        // Rajzolás
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        // Minden szakasz kirajzolása
        for (int i = 0; i < lineCount; ++i) {
            SDL_RenderDrawLine(renderer, lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2);
        }

        SDL_RenderPresent(renderer);
    }

    // Tisztítás és kilépés
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
