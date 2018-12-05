#include "fonction.h"
#include <SDL.h>
#include <math.h>
#include "creator.h"

void gravite_monstre(monstre *m, monde monde){
  if(estAuSol_monstre(m, monde)){
    m->velocity_y = 0;
    m->velocity_x = 0;
    if(m->saut || m->saut == -1){
      m->velocity_y = VELOCITE_MAX_MONSTRE;
      m->velocity_x = m->saut * VELOCITE_MAX_MONSTRE;
    }
  }else{
    if(m->velocity_y > -15){ //Si la vitesse devient trop grande les collisions ne sont plus respectées
      m->velocity_y -= 1;
      if(m->saut == 1){
	sautDroite_monstre(m);
      }else if(m->saut == -1){
	sautGauche_monstre(m);
      }
    }
  }
  m->x += m->velocity_x;
  m->y += m->velocity_y;
}


int estAuSol_monstre(monstre *m, monde monde){
  int yMonde = (m->y - HAUTEUR_MONSTRE)/TAILLE_BLOCS;
  int xMonde = m->x/TAILLE_BLOCS;
  int i, posMonstre;

  for(i = 0; i < TAILLE_BLOCS; i++){
    posMonstre = m->y - HAUTEUR_MONSTRE;
    if(posMonstre - i == (monde.grilleInt[TMONDE - yMonde][xMonde] == TERRE)*(yMonde)*TAILLE_BLOCS ||
      (posMonstre - i) == (monde.grilleInt[TMONDE - yMonde][xMonde + 1] == TERRE)*(yMonde)*TAILLE_BLOCS){
      if(!m->saut && m->saut != -1){
      	m->y = yMonde*TAILLE_BLOCS + HAUTEUR_MONSTRE;
      }
      return 1;
    }
  }
  return 0;
}

void sautDroite_monstre(monstre *m){
  if(m->velocity_y < 0){
    m->velocity_x -= 1;
  }else if(m->velocity_x > 0){
    m->velocity_x += 1;
  }
}


void sautGauche_monstre(monstre *m){
  if(m->velocity_y < 0){
    m->velocity_x += 1;
  }else if(m->velocity_x < 0){
    m->velocity_x -= 1;
  }
}


void collision_monstre(monstre *m, monde monde){
  int yMonde = m->y/TAILLE_BLOCS;
  int xMonde = m->x/TAILLE_BLOCS;
  int i;
  // printf("(n+1:%d, n:%d)\n", monde.grilleInt[(TMONDE - yMonde) +1][xMonde], monde.grilleInt[(TMONDE - yMonde)][xMonde]);
  for(i = 0; i < HAUTEUR_MONSTRE; i++){
    yMonde = (m->y - HAUTEUR_MONSTRE - i)/TAILLE_BLOCS;
    if(m->x >= (monde.grilleInt[(TMONDE - yMonde)][xMonde] == TERRE)*(xMonde)*TAILLE_BLOCS &&
      m->x <= ((monde.grilleInt[(TMONDE - yMonde)][xMonde] == TERRE)*(xMonde+1)*TAILLE_BLOCS)-1){
          // printf("Premiere condition\n");
      m->x = (xMonde*TAILLE_BLOCS);
    }
    xMonde = m->x + LARGEUR_MONSTRE/TAILLE_BLOCS;
    if(m->x + LARGEUR_MONSTRE >= (monde.grilleInt[TMONDE - (yMonde)][xMonde] == TERRE)*(xMonde)*TAILLE_BLOCS &&
      m->x + LARGEUR_MONSTRE <= ((monde.grilleInt[TMONDE - (yMonde)][xMonde] == TERRE)*(xMonde+1)*TAILLE_BLOCS)-1){
      // printf("Seconde condition\n");
      m->x = xMonde*TAILLE_BLOCS - LARGEUR_MONSTRE;
    }
  }
  // printf("wow\n");
}
