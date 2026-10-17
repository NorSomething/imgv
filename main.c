#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>

int main(int argc, char** argv) {

    int flag_v = 0;

    if (argc < 2) {
        printf("Usage: ./imgv <img_name>\n");
        exit(1);
    }

    if (argv[2] == NULL) {
        printf("No -v\n");
    }
    else {
        if (strncmp(argv[2], "-v", 2) == 0) {
            printf("The -v has been entered!\n");
            flag_v = 1;
        }
    }

    char* img_name = argv[1];

    int _ = SDL_Init(SDL_INIT_VIDEO);
    if (_ == -1) {
        printf("Error intializing SDL\n");
        exit(1);
    }

    //make this like accoridng to image size (scaled hopefully) later
    int flags = 0; //why this not work in i3wm? --> it auto tiles the imgv window instead of making it flaoting from the start

    if (flag_v == 1) {
        flags =  flags | SDL_WINDOW_RESIZABLE;
    }

    SDL_Window *window = SDL_CreateWindow("imgv", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,  1280, 720, flags);
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

    //get og img dimensions
    int img_w, img_h;
    SDL_QueryTexture(img_texture, NULL, NULL, &img_w, &img_h);

    float zoom = 1.0f;
    SDL_Rect dst = {
        (1280 - img_w) / 2,
        (720 - img_h) / 2,
        img_w,
        img_h
    };

    //draw first time
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, img_texture, NULL, &dst);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    int running = 1;

    int w,h;

    while(running) {
        while(SDL_PollEvent(&event)) {

            if (event.type == SDL_Quit) {
                running = 0;
            }

            if (event.type == SDL_KEYDOWN) {

                float old_zoom = zoom;
                float new_zoom = zoom;

                switch (event.key.keysym.sym) {
                    case SDLK_q:
                        printf("Q key pressed..\nExiting..\n");
                        running = 0;
                        break;

                    case SDLK_EQUALS:
                    case SDLK_PLUS:
                        printf("+ key pressed..\nZooming in..\n");
                        new_zoom = zoom * 1.25f;
                        break;

                    case SDLK_MINUS:
                        printf("- key pressed..\nZooming out..\n");
                        new_zoom = zoom * 1.25f;
                        break;

                    default:
                        break;

                }

                //clamping img
                if (new_zoom < 0.1f)
                    new_zoom = 0.1;

                if (new_zoom > 10.0f)
                    new_zoom = 10.0f;

                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, img_texture, NULL, &dst); //draw in whole window
                SDL_RenderPresent(renderer);


            }

        }

    }

    SDL_DestroyTexture(img_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}
