#include "fonction.h"
#include "creator.h"



void detruire_atlas(atlas* atlas){
  for(int i = 0; i < NBIMAGES; i++){
    detruire_text(atlas->tabIm[i]);
  }
  free(atlas);
}

void detruire_text(image* image){
  SDL_FreeSurface(image->surface);
  free(image);
  image = NULL;
}

void detruire_monde(monde *monde){
  desallouer_tab_2D_int(monde->grilleInt, TMONDE);
  desallouer_tab_2D_char(monde->grilleChar, TMONDE);
  desallouer_tab_2D_int(monde->posB, TMONDE);
  desallouer_tab_2D_int(monde->posBY,TMONDE);
  desallouer_tab_2D_int(monde->affichage, NBBLOCS_FENETREY);
}
