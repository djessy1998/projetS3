#pragma once
#include <SDL.h>

typedef struct image {
  SDL_Surface* surface;
  SDL_Rect pos;
  SDL_Rect anim;
} image;


typedef struct atlas {
    image* tabIm[20];
} atlas;