#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "constants.h"
#include "game.h"

int main() {
    srand(time(0));
    int grid[GRID_SIZE*GRID_SIZE] = {0};
    spawn_random_tile(grid);
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL failed to initialize: %s\n", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow(
        "2048",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );
    if(window == NULL) {
        fprintf(stderr, "SDL window failed to initialize: %s\n", SDL_GetError());
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) {
        fprintf(stderr, "SDL renderer failed to initialize: %s\n", SDL_GetError());
    }
    SDL_Rect srcRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 512;
    srcRect.h = 512;
    SDL_Surface* surfaces[IMG_COUNT] = {
        SDL_LoadBMP("./img/tile_2.bmp"),
        SDL_LoadBMP("./img/tile_4.bmp"),
        SDL_LoadBMP("./img/tile_8.bmp"),
        SDL_LoadBMP("./img/tile_16.bmp"),
        SDL_LoadBMP("./img/tile_32.bmp"),
        SDL_LoadBMP("./img/tile_64.bmp"),
        SDL_LoadBMP("./img/tile_128.bmp"),
        SDL_LoadBMP("./img/tile_256.bmp"),
        SDL_LoadBMP("./img/tile_512.bmp"),
        SDL_LoadBMP("./img/tile_1024.bmp"),
        SDL_LoadBMP("./img/tile_2048.bmp"),
        SDL_LoadBMP("./img/tile_4096.bmp"),
        SDL_LoadBMP("./img/tile_8192.bmp"),
        SDL_LoadBMP("./img/tile_16384.bmp"),
    };
    SDL_Texture* textures[IMG_COUNT] = {0};
    for(int i = 0; i < IMG_COUNT; i++) {
        textures[i] = SDL_CreateTextureFromSurface(renderer, surfaces[i]);
    }
    SDL_Event event;
    char quit = 0;
    while(!quit) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) quit = 1;
            if(event.type == SDL_KEYDOWN) {
                int x = 0;
                int y = 0;
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        y = -1;
                        break;
                    case SDLK_DOWN:
                        y = 1;
                        break;
                    case SDLK_LEFT:
                        x = -1;
                        break;
                    case SDLK_RIGHT:
                        x = 1;
                        break;
                    default:
                        break;
                }
                if((x != 0 || y != 0) && slide(grid, x, y)) {
                    spawn_random_tile(grid);
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 238, 228, 218, 255);
        SDL_RenderClear(renderer);
        for(int i = 0; i < GRID_SIZE; i++) {
            for(int j = 0; j < GRID_SIZE; j++) {
                SDL_Rect destRect;
                destRect.x = j * 100;
                destRect.y = i * 100;
                destRect.w = 100;
                destRect.h = 100;
                int value = grid[i*GRID_SIZE+j];
                if(value != 0) {
                    switch(value) {
                        case 2:
                        SDL_RenderCopy(renderer, textures[0], &srcRect, &destRect);
                        break;
                        case 4:
                        SDL_RenderCopy(renderer, textures[1], &srcRect, &destRect);
                        break;
                        case 8:
                        SDL_RenderCopy(renderer, textures[2], &srcRect, &destRect);
                        break;
                        case 16:
                        SDL_RenderCopy(renderer, textures[3], &srcRect, &destRect);
                        break;
                        case 32:
                        SDL_RenderCopy(renderer, textures[4], &srcRect, &destRect);
                        break;
                        case 64:
                        SDL_RenderCopy(renderer, textures[5], &srcRect, &destRect);
                        break;
                        case 128:
                        SDL_RenderCopy(renderer, textures[6], &srcRect, &destRect);
                        break;
                        case 256:
                        SDL_RenderCopy(renderer, textures[7], &srcRect, &destRect);
                        break;
                        case 512:
                        SDL_RenderCopy(renderer, textures[8], &srcRect, &destRect);
                        break;
                        case 1024:
                        SDL_RenderCopy(renderer, textures[9], &srcRect, &destRect);
                        break;
                        case 2048:
                        SDL_RenderCopy(renderer, textures[10], &srcRect, &destRect);
                        break;
                        case 4096:
                        SDL_RenderCopy(renderer, textures[11], &srcRect, &destRect);
                        break;
                        case 8192:
                        SDL_RenderCopy(renderer, textures[12], &srcRect, &destRect);
                        break;
                        case 16384:
                        SDL_RenderCopy(renderer, textures[13], &srcRect, &destRect);
                        break;
                    }
                }
            }
        }
        SDL_RenderPresent(renderer);
    }
    for(int i = 0; i < IMG_COUNT; i++) {
        SDL_DestroyTexture(textures[i]);
    }
    for(int i = 0; i < IMG_COUNT; i++) {
        SDL_FreeSurface(surfaces[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}