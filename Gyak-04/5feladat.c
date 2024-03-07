#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAX_RECT_COUNT 100

typedef struct {
    SDL_Rect rect; // Téglalap koordinátái és mérete
    SDL_Color color; // Szín
} Rectangle;

// Színpaletta színei
SDL_Color palette[] = {
    {255, 0, 0, 255},    // Piros
    {0, 255, 0, 255},    // Zöld
    {0, 0, 255, 255},    // Kék
    {255, 255, 0, 255},  // Sárga
    {255, 0, 255, 255},  // Lila
    {0, 255, 255, 255},  // Cian
};

int paletteSize = sizeof(palette) / sizeof(palette[0]);
int currentColorIndex = 0;

int main(int argc, char* argv[]) {
    // SDL inicializálása
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Nem sikerült inicializálni az SDL-t: %s\n", SDL_GetError());
        return 1;
    }

    // Ablak létrehozása
    SDL_Window* window = SDL_CreateWindow("Téglalap rajzoló", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    // Téglalapok tömbje
    Rectangle rectangles[MAX_RECT_COUNT];
    int rectCount = 0;

    // Az eseménykezelő változó
    SDL_Event event;

    // Fő ciklus
    int quit = 0;
    while (!quit) {
        // Események kezelése
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                // Egérkattintás eseménye
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (event.button.y < SCREEN_HEIGHT - 50) {
                        // Téglalap hozzáadása a tömbhöz a bal alsó paletta részen történő kattintáskor
                        if (rectCount < MAX_RECT_COUNT) {
                            rectangles[rectCount].rect.x = event.button.x - 25; // középre helyezés
                            rectangles[rectCount].rect.y = event.button.y - 25; // középre helyezés
                            rectangles[rectCount].rect.w = 50;
                            rectangles[rectCount].rect.h = 50;
                            rectangles[rectCount].color = palette[currentColorIndex];
                            rectCount++;
                        }
                    } else {
                        // Szín kiválasztása a palettán
                        int selectedColorIndex = event.button.x / (SCREEN_WIDTH / paletteSize);
                        if (selectedColorIndex < paletteSize) {
                            currentColorIndex = selectedColorIndex;
                        }
                    }
                }
            }
        }

        // Rajzolás
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Paletta kirajzolása
        for (int i = 0; i < paletteSize; ++i) {
            SDL_Rect rect = {i * (SCREEN_WIDTH / paletteSize), SCREEN_HEIGHT - 50, SCREEN_WIDTH / paletteSize, 50};
            SDL_SetRenderDrawColor(renderer, palette[i].r, palette[i].g, palette[i].b, palette[i].a);
            SDL_RenderFillRect(renderer, &rect);
        }

        // Minden téglalap kirajzolása
        for (int i = 0; i < rectCount; ++i) {
            SDL_SetRenderDrawColor(renderer, rectangles[i].color.r, rectangles[i].color.g, rectangles[i].color.b, rectangles[i].color.a);
            SDL_RenderFillRect(renderer, &rectangles[i].rect);
        }

        SDL_RenderPresent(renderer);
    }

    // Tisztítás és kilépés
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
