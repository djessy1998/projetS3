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
  bloc_dans_monstre(m, monde);
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


int bloc_dans_monstre(monstre *m, monde monde){
  // printf("y=%d\nx=%d\n", m->y/TAILLE_BLOCS, m->x/TAILLE_BLOCS);
  int yMonde = (m->y)/TAILLE_BLOCS;
  int yMondePied = (m->y - HAUTEUR_MONSTRE)/TAILLE_BLOCS;

  int xMonde = ((m->x)/TAILLE_BLOCS);
  int xMondeMid = ((m->x + (LARGEUR_MONSTRE/2))/TAILLE_BLOCS);
  int xMondeDroite = ((m->x + LARGEUR_MONSTRE-1)/TAILLE_BLOCS);

  if(monde.grilleInt[TMONDE - yMonde][xMonde] == TERRE && monde.grilleInt[TMONDE - yMondePied][xMonde] == TERRE &&
    monde.grilleInt[TMONDE - yMonde][xMondeMid] == TERRE && monde.grilleInt[TMONDE - yMondePied][xMondeMid] == TERRE &&
    monde.grilleInt[TMONDE - yMonde][xMondeDroite] == TERRE &&monde.grilleInt[TMONDE - yMondePied][xMondeDroite] == TERRE){
    m->y = (yMonde+1)*TAILLE_BLOCS;
    return 1;
  }
  if(monde.grilleInt[TMONDE - yMonde][xMonde] == TERRE && monde.grilleInt[TMONDE - yMondePied][xMonde] == TERRE){
    //Dans un bloc a GAUCHE
    m->x = (xMonde+1)*TAILLE_BLOCS;
    return 1;
  }
  if(monde.grilleInt[TMONDE - yMonde][xMondeMid] == TERRE && monde.grilleInt[TMONDE - yMondePied][xMondeMid] == TERRE){
    //Dans un bloc au MILIEU
    m->x = (xMonde-1)*TAILLE_BLOCS;
    return 1;
  }
  if(monde.grilleInt[TMONDE - yMonde][xMondeDroite] == TERRE && monde.grilleInt[TMONDE - yMondePied][xMondeDroite] == TERRE){
    //Dans un bloc au MILIEU
    m->x = (xMonde-1)*TAILLE_BLOCS;
    return 1;
  }
  return 0;
}
