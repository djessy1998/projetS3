#include "fonction.h"
#include <SDL.h>
#include <math.h>
#include "creator.h"

void gravite_monstre(monstre *m, monde monde){
  if(/*estAuSol_monstre(m, monde)*/1){
    m->velocity_y = 0;
    m->velocity_x = 0;
    if(m->saut){
      m->velocity_y = VELOCITE_MAX*10;
      m->velocity_x = VELOCITE_MAX*10;
    }
  }else{
    m->velocity_y -= 1;
    // m->velocity_x -= 1;
  }
  m->x += m->velocity_x;
  m->y += m->velocity_y;
}


int estAuSol_monstre(monstre *m, monde monde){
  int yMonde = (m->y-22)/TAILLE_BLOCS; //2 hauteur du monstre
  int xMonde = m->x/TAILLE_BLOCS;
  int i;
  for(i = 0; i < TAILLE_BLOCS; i++){
    if(m->y - 22 - i == (monde.grilleInt[yMonde][xMonde]%2)*(yMonde)*TAILLE_BLOCS){
      m->y = (yMonde)*TAILLE_BLOCS;
      return 1;
    }
  }
  return 0;
}
