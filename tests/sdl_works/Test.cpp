#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

int main(int argc, char **argv) {
  SDL_Surface *hello = NULL;
  SDL_Surface *screen = NULL;
  SDL_Init(SDL_INIT_EVERYTHING);
  screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
  hello = SDL_CreateRGBSurface(SDL_SWSURFACE, 640, 480, 32, 0, 0, 0, 0);
  SDL_BlitSurface(hello, NULL, screen, NULL);
  SDL_Flip(screen);
  SDL_Delay(2000);
  (void) argc;
  (void) argv;
  return 0;
}
