#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char** argv) {

    if (argc != 2) {
        printf("Usage: ./imgv <img_name>\n");
        exit(1);
    }

    char* img_name = argv[1];

    int _ = SDL_Init(SDL_INIT_VIDEO);
    if (_ == -1) {
        printf("Error intializing SDL\n");
        exit(1);
    }

    //make this like accoridng to image size (scaled hopefully) later
    SDL_Window *window = SDL_CreateWindow("imgv", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    if (window == NULL) {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *img_texture = IMG_LoadTexture(renderer, img_name);
    if (img_texture == NULL) {
        printf("Error creating image texture: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // SDL_RenderClear(renderer);
    // SDL_RenderCopy(renderer, img_texture, NULL, NULL); //draw in whole window
    // SDL_RenderPresent(renderer);

    int run = 1;
    while(run) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, img_texture, NULL, NULL); //draw in whole window
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}
