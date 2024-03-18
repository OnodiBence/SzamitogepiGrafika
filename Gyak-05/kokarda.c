#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h> // A rand() és srand() függvények használatához
#include <time.h>   // Az idő alapján történő inicializáláshoz

// #define SCREEN_WIDTH 640
// #define SCREEN_HEIGHT 480
// #define PADDLE_WIDTH 10
// #define PADDLE_HEIGHT 100
// #define BALL_SIZE 10
// #define PADDLE_SPEED 5
// #define BALL_SPEED 3

// SDL_Window* window = NULL;
// SDL_Renderer* renderer = NULL;
// SDL_Rect leftPaddle = {10, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT};
// SDL_Rect rightPaddle = {SCREEN_WIDTH - 20, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT};
// SDL_Rect ball = {SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT / 2 - BALL_SIZE / 2, BALL_SIZE, BALL_SIZE};
// int ballXVel = BALL_SPEED;
// int ballYVel = BALL_SPEED;

// // A paddle mozgatása felfelé
// void movePaddleUp(SDL_Rect* paddle) {
//     paddle->y -= PADDLE_SPEED;
//     if (paddle->y < 0) {
//         paddle->y = 0;
//     }
// }

// // A paddle mozgatása lefelé
// void movePaddleDown(SDL_Rect* paddle) {
//     paddle->y += PADDLE_SPEED;
//     if (paddle->y > SCREEN_HEIGHT - PADDLE_HEIGHT) {
//         paddle->y = SCREEN_HEIGHT - PADDLE_HEIGHT;
//     }
// }

// // A labda mozgatása
// void moveBall() {
//     ball.x += ballXVel;
//     ball.y += ballYVel;

//     // A labda ütközése a falakkal
//     if (ball.y <= 0 || ball.y >= SCREEN_HEIGHT - BALL_SIZE) {
//         ballYVel = -ballYVel;
//     }

//     // A labda ütközése a paddle-ekkel
//     if (SDL_HasIntersection(&ball, &leftPaddle) || SDL_HasIntersection(&ball, &rightPaddle)) {
//         ballXVel = -ballXVel;
//     }

//     // A labda áthaladása a paddle-eken
//     if (ball.x <= 0 || ball.x >= SCREEN_WIDTH - BALL_SIZE) {
//         ball.x = SCREEN_WIDTH / 2 - BALL_SIZE / 2;
//         ball.y = SCREEN_HEIGHT / 2 - BALL_SIZE / 2;
//         ballXVel = -ballXVel;
//     }
// }

// // A játék frissítése
// void update() {
//     const Uint8* keystate = SDL_GetKeyboardState(NULL);

//     if (keystate[SDL_SCANCODE_W]) {
//         movePaddleUp(&leftPaddle);
//     }
//     if (keystate[SDL_SCANCODE_S]) {
//         movePaddleDown(&leftPaddle);
//     }
//     if (keystate[SDL_SCANCODE_UP]) {
//         movePaddleUp(&rightPaddle);
//     }
//     if (keystate[SDL_SCANCODE_DOWN]) {
//         movePaddleDown(&rightPaddle);
//     }

//     moveBall();
// }

// // A játék kirajzolása
// void render() {
//     SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Háttér színe fehér
//     SDL_RenderClear(renderer);

//     // Paddle-ök rajzolása
//     SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Bal paddle piros
//     SDL_RenderFillRect(renderer, &leftPaddle);
//     SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Jobb paddle kék
//     SDL_RenderFillRect(renderer, &rightPaddle);

//     // Labda rajzolása
//     SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Labda zöld
//     SDL_RenderFillRect(renderer, &ball);

//     SDL_RenderPresent(renderer);
// }

// // A felszabadítja az erőforrásokat
// void cleanup() {
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();
// }

// int main(int argc, char* args[]) {
//     SDL_Init(SDL_INIT_VIDEO);
//     window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//     renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

//     bool running = true;
//     while (running) {
//         SDL_Event event;
//         while (SDL_PollEvent(&event)) {
//             if (event.type == SDL_QUIT) {
//                 running = false;
//             }
//         }

//         update();
//         render();
//         SDL_Delay(1000 / 60);
//     }

//     cleanup();
//     return 0;
// }
#include <SDL2/SDL_ttf.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 100
#define BALL_SIZE 10
#define PADDLE_SPEED 5
#define BALL_SPEED 3
#define FONT_SIZE 32

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect leftPaddle = {10, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT};
SDL_Rect rightPaddle = {SCREEN_WIDTH - 20, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT};
SDL_Rect ball = {SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT / 2 - BALL_SIZE / 2, BALL_SIZE, BALL_SIZE};
int ballXVel = BALL_SPEED;
int ballYVel = BALL_SPEED;

TTF_Font* font = NULL;

// Betűtípus betöltése
bool loadFont() {
    if (TTF_Init() == -1) {
        printf("SDL_ttf initialization failed: %s\n", TTF_GetError());
        return false;
    }

    font = TTF_OpenFont("arial.ttf", FONT_SIZE);
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return false;
    }

    return true;
}

// Betűtípus felszabadítása
void closeFont() {
    TTF_CloseFont(font);
    font = NULL;
    TTF_Quit();
}

// A paddle mozgatása felfelé
void movePaddleUp(SDL_Rect* paddle) {
    paddle->y -= PADDLE_SPEED;
    if (paddle->y < 0) {
        paddle->y = 0;
    }
}

// A paddle mozgatása lefelé
void movePaddleDown(SDL_Rect* paddle) {
    paddle->y += PADDLE_SPEED;
    if (paddle->y > SCREEN_HEIGHT - PADDLE_HEIGHT) {
        paddle->y = SCREEN_HEIGHT - PADDLE_HEIGHT;
    }
}

// A labda mozgatása
void moveBall() {
    ball.x += ballXVel;
    ball.y += ballYVel;

    // A labda ütközése a falakkal
    if (ball.y <= 0 || ball.y >= SCREEN_HEIGHT - BALL_SIZE) {
        ballYVel = -ballYVel;
    }

    // A labda ütközése a paddle-ekkel
    if (SDL_HasIntersection(&ball, &leftPaddle) || SDL_HasIntersection(&ball, &rightPaddle)) {
        ballXVel = -ballXVel;
    }

    // A labda áthaladása a paddle-eken
    if (ball.x <= 0 || ball.x >= SCREEN_WIDTH - BALL_SIZE) {
        printf("Game Over\n");
        SDL_Delay(3000); // Vár 3 másodpercet
        ball.x = SCREEN_WIDTH / 2 - BALL_SIZE / 2;
        ball.y = SCREEN_HEIGHT / 2 - BALL_SIZE / 2;
        ballXVel = BALL_SPEED;
        ballYVel = BALL_SPEED;
    }
}

// A játék frissítése
void update() {
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_W]) {
        movePaddleUp(&leftPaddle);
    }
    if (keystate[SDL_SCANCODE_S]) {
        movePaddleDown(&leftPaddle);
    }
    if (keystate[SDL_SCANCODE_UP]) {
        movePaddleUp(&rightPaddle);
    }
    if (keystate[SDL_SCANCODE_DOWN]) {
        movePaddleDown(&rightPaddle);
    }

    moveBall();
}

// A játék kirajzolása
void render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Háttér színe fehér
    SDL_RenderClear(renderer);

    // Paddle-ök rajzolása
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Bal paddle piros
    SDL_RenderFillRect(renderer, &leftPaddle);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Jobb paddle kék
    SDL_RenderFillRect(renderer, &rightPaddle);

    // Labda rajzolása
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Labda zöld
    SDL_RenderFillRect(renderer, &ball);

    // "Game Over" felirat kirajzolása
    if (ball.x <= 0 || ball.x >= SCREEN_WIDTH - BALL_SIZE) {
        SDL_Color textColor = {255, 0, 0}; // Vörös szöveg
        SDL_Surface* surface = TTF_RenderText_Solid(font, "Game Over", textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect textRect = {SCREEN_WIDTH / 2 - surface->w / 2, SCREEN_HEIGHT / 2 - surface->h / 2, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &textRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    SDL_RenderPresent(renderer);
}

// A felszabadítja az erőforrásokat
void cleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    closeFont();
    SDL_Quit();
}

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!loadFont()) {
        cleanup();
        return 1;
    }

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        update();
        render();
        SDL_Delay(1000 / 60);
    }

    cleanup();
    return 0;
}