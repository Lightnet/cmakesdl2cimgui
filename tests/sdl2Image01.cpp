// https://gist.github.com/fschr/a8476f8993e5b9a60aa1c7ec4af3704b
// compile with: clang++ main.cpp -o image_exmple -lSDL2 -lSDL2_image
// https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/index2.php
// https://gamedev.stackexchange.com/questions/59078/sdl-function-for-loading-pngs
//Using SDL, SDL_image, standard IO, and strings
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>
#define main SDL_main
#undef main

int main(void) {
    SDL_Event event;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_Window *window = NULL;

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(
        500, 500,
        0, &window, &renderer
    );
    IMG_Init(IMG_INIT_PNG);
    texture = IMG_LoadTexture(renderer, "images/hello_world.png");
    while (1) {
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyTexture(texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}