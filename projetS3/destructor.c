#include "fonction.h"
#include "creator.h"



void detruire_atlas(atlas* atlas){
  for(int i = 0; i < NBIMAGES; i++){
    detruire_text(atlas->tabIm[i]);
  }
}

void detruire_text(image* image){
  SDL_FreeSurface(image->surface);
  free(image);
  image = NULL;
}
