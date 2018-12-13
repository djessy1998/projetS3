#pragma once
#include <SDL.h>

#define NBIMAGES	41

typedef struct image {
  SDL_Surface* surface;
  SDL_Rect pos;
  SDL_Rect anim;
} image;


typedef struct atlas {
    image* tabIm[NBIMAGES];
} atlas;


//atlas.c
image* creer_texture(char* chemin, int x, int y, int animX, int animY, int animH, int animW);
atlas* init_atlas();
int getPosX(image* image);
int getPosY(image* image);
void setPosX(image* image, int x);
void setPosY(image* image, int y);
void setAnimX(image* image, int x);
void setAnimY(image* image, int y);
void setAnimH(image* image, int h);
void setAnimW(image* image, int w);
void setPosH(image* image, int h);
void setPosW(image* image, int w);
