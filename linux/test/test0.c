#include <SDL2/SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 300
#define SCREEN_HEIGHT 200
#define VRAM_WIDTH 300
#define VRAM_HEIGHT 200

SDL_Window* window = NULL;
SDL_Surface* surface = NULL;
Uint32 vram[VRAM_WIDTH][VRAM_HEIGHT];

void drawPixel(int x, int y, Uint32 color) {
    if (x >= 0 && x < VRAM_WIDTH && y >= 0 && y < VRAM_HEIGHT) {
        vram[x][y] = color;
    }
}

void drawRect(int x, int y, int width, int height, Uint32 color) {
    for (int i = x; i < x + width; i++) {
        for (int j = y; j < y + height; j++) {
            drawPixel(i, j, color);
        }
    }
}

void renderVRAM() {
    SDL_LockSurface(surface);

    Uint32* pixels = (Uint32*)surface->pixels;

    for (int x = 0; x < VRAM_WIDTH; x++) {
        for (int y = 0; y < VRAM_HEIGHT; y++) {
            pixels[y * VRAM_WIDTH + x] = vram[x][y];
        }
    }

    SDL_UnlockSurface(surface);
    SDL_UpdateWindowSurface(window);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("VRAM Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        return 1;
    }

    surface = SDL_GetWindowSurface(window);

    // Clear VRAM
    memset(vram, 0, sizeof(vram));

    // Draw some shapes on VRAM
    drawRect(10, 10, 100, 50, SDL_MapRGB(surface->format, 255, 0, 0));
    drawRect(50, 100, 150, 100, SDL_MapRGB(surface->format, 0, 255, 0));

    // Render VRAM to window surface
    renderVRAM();

    // Main loop
    SDL_Event event;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
