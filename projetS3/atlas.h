#pragma once
#include <SDL.h>

typedef struct image {
  SDL_Surface* surface;
  SDL_Rect pos;
  SDL_Rect anim;
} image;


typedef struct atlas {
	  image* character;
	  image* vieEnt;
  	image* casque;
  	image* armure;
  	image* invIm;
  	image* ActuelInv;
  	image* miVie;
  	image* noVie;
  	image* Crack;
  	image* characterD;
  	image* tronc;
  	image* abg;
  	image* abd;
  	image* topArb;
  	image* basArb;
  	image* map;
  	image* Image_Monstre;
  	image* fond_grotte;
  	image* terre;
    image* bg;
    image* screen;
} atlas;