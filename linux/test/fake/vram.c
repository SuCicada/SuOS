//
// Created by SuCicada on 2023/06/26.
//
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "color.h"

//#define SCREEN_WIDTH 300
//#define SCREEN_HEIGHT 200
//#define VRAM_WIDTH 300
//#define VRAM_HEIGHT 200
int VRAM_WIDTH;
int VRAM_HEIGHT;

SDL_Window *window = NULL;
SDL_Surface *surface = NULL;
Uint32 *vram;

void renderVRAM() {
    SDL_LockSurface(surface);

    Uint32 *pixels = (Uint32 *) surface->pixels;

    for (int x = 0; x < VRAM_WIDTH; x++) {
        for (int y = 0; y < VRAM_HEIGHT; y++) {
            pixels[y * VRAM_WIDTH + x] = vram[x + VRAM_WIDTH * y];
        }
    }

    SDL_UnlockSurface(surface);
    SDL_UpdateWindowSurface(window);
}

DECLSPEC Uint32 SDLCALL map_color(int color_flag) {
    int r = rgb_table[3 * color_flag + 0];
    int g = rgb_table[3 * color_flag + 1];
    int b = rgb_table[3 * color_flag + 2];
    return SDL_MapRGB(surface->format, r, g, b);
}

int vram_simulator(const unsigned char *vram0, int xsize, int ysize) {
//    unsigned char *vram0 = (unsigned char *) malloc(sizeof(unsigned char) * xsize * ysize);
//    memcpy(vram0, _vram0, sizeof(unsigned char) * xsize * ysize);

    VRAM_WIDTH = xsize;
    VRAM_HEIGHT = ysize;
    vram = (Uint32 *) malloc(sizeof(Uint32) * VRAM_WIDTH * VRAM_HEIGHT);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        return 1;
    }
    int SCREEN_WIDTH = VRAM_WIDTH, SCREEN_HEIGHT = VRAM_HEIGHT;
    window = SDL_CreateWindow("VRAM Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        return 1;
    }

    surface = SDL_GetWindowSurface(window);

//    memcpy(vram, vram0, sizeof(vram));
    // Clear VRAM
//    memset(vram, 0, sizeof(vram));

    // Draw some shapes on VRAM
//    drawRect(10, 10, 100, 50, SDL_MapRGB(surface->format, 255, 0, 0));
//    drawRect(50, 100, 150, 100, SDL_MapRGB(surface->format, 0, 255, 0));

    for(int i = 0; i < VRAM_WIDTH * VRAM_HEIGHT; i++) {
        vram[i] = map_color(vram0[i]);
    }

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

//    return 0;
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
