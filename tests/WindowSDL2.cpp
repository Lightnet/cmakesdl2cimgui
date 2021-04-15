// https://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2

#include "SDL.h"

int main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_VIDEO);
  const int WIDTH = 640, HEIGHT = 480;

  SDL_Window *window = SDL_CreateWindow(
    "SDL2Test",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    WIDTH,
    HEIGHT,
    0
  );

  SDL_Log("Setup SDL2 Window ");

  if (window == nullptr){
    SDL_Log("Could not create a window: %s", SDL_GetError());
    return -1;
  }

  //SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr){
    SDL_Log("Could not create a renderer: %s", SDL_GetError());
    return -1;
  }
  
  bool isRunning = true;
  while (isRunning)
  {
    // Get the next event
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        isRunning = false;
        // Break out of the loop on quit
        break;
      }
      //SDL_Log("render"); //test console log
      // Set the color to cornflower blue and clear
      SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
      //SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      // Clear window
      SDL_RenderClear( renderer );
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

      // Show the renderer contents
      SDL_RenderPresent(renderer);
    }
  }
  // Clean up
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}