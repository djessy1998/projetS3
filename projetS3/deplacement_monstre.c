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
  int xMondeDroite = (m->x+LARGEUR_MONSTRE)/TAILLE_BLOCS;
  int i, posMonstre;

  for(i = 0; i < TAILLE_BLOCS; i++){
    posMonstre = m->y - HAUTEUR_MONSTRE;
    if(posMonstre - i == (monde.grilleInt[TMONDE - yMonde][xMonde] == TERRE)*(yMonde)*TAILLE_BLOCS ||
      (posMonstre - i) == (monde.grilleInt[TMONDE - yMonde][xMondeDroite] == TERRE)*(yMonde)*TAILLE_BLOCS){
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
  int yMondeTete = (m->y)/TAILLE_BLOCS  +1;
  int yMondePied = (m->y - HAUTEUR_MONSTRE)/TAILLE_BLOCS  +1;

  int xMonde = ((m->x)/TAILLE_BLOCS);
  int xMondeMid = ((m->x + (LARGEUR_MONSTRE/2))/TAILLE_BLOCS);
  int xMondeDroite = ((m->x + LARGEUR_MONSTRE-1)/TAILLE_BLOCS);

  if((monde.grilleInt[TMONDE - yMondeTete][xMonde] == TERRE && monde.grilleInt[TMONDE - yMondePied][xMonde] == TERRE) &&
    (monde.grilleInt[TMONDE - yMondeTete][xMondeMid] == TERRE && monde.grilleInt[TMONDE - yMondePied][xMondeMid] == TERRE) &&
    (monde.grilleInt[TMONDE - yMondeTete][xMondeDroite] == TERRE && monde.grilleInt[TMONDE - yMondePied][xMondeDroite] == TERRE)){
    m->y = (yMondeTete)*TAILLE_BLOCS + HAUTEUR_MONSTRE; // On le fait monter
    printf("Condition ligne 79\n");
  }else{

    printf("///////// DEBUT DE CONDITION /////////\n");
    //GAUCHE
    if(monde.grilleInt[TMONDE - yMondeTete][xMonde] == TERRE || monde.grilleInt[TMONDE - yMondePied][xMonde] == TERRE){
      printf("Condition ligne 86 bloc en HAUT a GAUCHE et a GAUCHE\n");
      m->x = (xMonde+1)*TAILLE_BLOCS; //On le décale à Droite
      m->velocity_x = 0;
      m->velocity_y = 0; // On arrête le saut
    }


    //DROITE
    if(monde.grilleInt[TMONDE - yMondeTete][xMondeDroite] == TERRE || monde.grilleInt[TMONDE - yMondePied][xMondeDroite] == TERRE){
      printf("Condition ligne 94 bloc en HAUT a DROITE et a DROITE\n");
      m->x = (xMonde)*TAILLE_BLOCS - 1; //On le décale à Gauche
      m->velocity_x = 0;
      m->velocity_y = 0; // On arrête le saut
    }


    //MILLIEU
    if(monde.grilleInt[TMONDE - yMondeTete][xMondeMid] == TERRE || monde.grilleInt[TMONDE - yMondePied][xMondeMid] == TERRE){
      printf("Condition ligne 104 bloc en HAUT au MILIEU et au MILIEU\n");
      m->y = (yMondePied)*TAILLE_BLOCS - HAUTEUR_MONSTRE; //On le fait descendre
      m->velocity_x = 0;
      m->velocity_y = 0; // On arrête le saut
    }
    printf("///////// FIN DE CONDITION /////////\n");
  }

  return 0;
}
