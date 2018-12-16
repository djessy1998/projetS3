#include "fonction.h"
#include <SDL.h>
#include <math.h>
#include "creator.h"
#include "constant.h"

void gravite_monstre(monstre *m, monde monde){
  //Si il y a un bloc au dessus le monstre ne sautera Parcours
  bloc_au_dessus(m, monde);
  if(estAuSol_monstre(m, monde)){
    m->velocity_y = 0;
    m->velocity_x = 0;
    if(m->saut == DROITE || m->saut == GAUCHE){
      m->velocity_y = VELOCITE_MAX_MONSTRE;
      m->velocity_x = m->saut * VELOCITE_MAX_MONSTRE;
    }
  }else{
    if(m->velocity_y > -15){ //Si la vitesse devient trop grande les collisions ne sont plus respectées
      m->velocity_y -= 1;
      if(m->saut == DROITE){
      	sautDroite_monstre(m);
      }else if(m->saut == GAUCHE){
      	sautGauche_monstre(m);
      }
    }
  }
  m->x += m->velocity_x;
  m->y += m->velocity_y;
  bloc_dans_monstre(m, monde);
}


int estAuSol_monstre(monstre *m, monde monde){
  //Calcul la position du monstre dans le tableau du monde
  int yMonde = (m->y - HAUTEUR_MONSTRE)/TAILLE_BLOCS;
  int xMonde = m->x/TAILLE_BLOCS;
  int xMondeDroite = (m->x+LARGEUR_MONSTRE)/TAILLE_BLOCS;
  int i, posMonstre;

  for(i = 0; i < TAILLE_BLOCS; i++){
    posMonstre = m->y - HAUTEUR_MONSTRE;
    if(posMonstre - i == (estSolide(monde.grilleInt[TMONDE - yMonde][xMonde]))*(yMonde)*TAILLE_BLOCS ||
      (posMonstre - i) == (estSolide(monde.grilleInt[TMONDE - yMonde][xMondeDroite]))*(yMonde)*TAILLE_BLOCS){
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
  m->dernierSaut = DROITE;
}


void sautGauche_monstre(monstre *m){
  if(m->velocity_y < 0){
    m->velocity_x += 1;
  }else if(m->velocity_x < 0){
    m->velocity_x -= 1;
  }
  m->dernierSaut = GAUCHE;
}


int bloc_dans_monstre(monstre *m, monde monde){
  //Limites du monde en X
  if(m->x < 0){
    m->x = 0;
  }else if(m->x + LARGEUR_MONSTRE > TMONDE*TAILLE_BLOCS){
    m->x = (TMONDE*TAILLE_BLOCS) - LARGEUR_MONSTRE-1;
  }

  //Limites du monde en Y
  if(m->y - HAUTEUR_MONSTRE < 0){
    m->y = HAUTEUR_MONSTRE +1;
  }else if(m->y > TMONDE*TAILLE_BLOCS){
    m->y = TMONDE*TAILLE_BLOCS - HAUTEUR_MONSTRE -1;
  }

  int yMondeTete = (m->y)/TAILLE_BLOCS  +1;
  int yMondePied = (m->y - HAUTEUR_MONSTRE)/TAILLE_BLOCS  +1;

  int xMonde = ((m->x)/TAILLE_BLOCS);
  int xMondeMid = ((m->x + (LARGEUR_MONSTRE/2))/TAILLE_BLOCS);
  int xMondeDroite = ((m->x + LARGEUR_MONSTRE-1)/TAILLE_BLOCS);

  //Si le monstre est bloqué (Toutes les cases qu'il occupe sont Solide)
  if(estSolide(monde.grilleInt[TMONDE - yMondeTete][xMonde]) && estSolide(monde.grilleInt[TMONDE - yMondePied][xMonde]) &&
    estSolide(monde.grilleInt[TMONDE - yMondeTete][xMondeMid]) && estSolide(monde.grilleInt[TMONDE - yMondePied][xMondeMid]) &&
    estSolide(monde.grilleInt[TMONDE - yMondeTete][xMondeDroite]) && estSolide(monde.grilleInt[TMONDE - yMondePied][xMondeDroite])){
    m->y = (yMondeTete)*TAILLE_BLOCS + HAUTEUR_MONSTRE; // On le fait monter
  }else{
    //GAUCHE
    if(estSolide(monde.grilleInt[TMONDE - yMondeTete][xMonde]) || estSolide(monde.grilleInt[TMONDE - yMondePied][xMonde])){
      m->x = (xMonde+1)*TAILLE_BLOCS; //On le décale à Droite
      m->velocity_x = 0;
      m->velocity_y = 0; // On arrête le saut
    }

    //DROITE
    if(estSolide(monde.grilleInt[TMONDE - yMondeTete][xMondeDroite]) || estSolide(monde.grilleInt[TMONDE - yMondePied][xMondeDroite])){
      m->x = (xMonde)*TAILLE_BLOCS - 1; //On le décale à Gauche
      m->velocity_x = 0;
      m->velocity_y = 0; // On arrête le saut
    }

    //MILLIEU
    if(estSolide(monde.grilleInt[TMONDE - yMondeTete][xMondeMid]) || estSolide(monde.grilleInt[TMONDE - yMondePied][xMondeMid])){
      m->y = (yMondePied)*TAILLE_BLOCS - HAUTEUR_MONSTRE; //On le fait descendre
      m->velocity_x = 0;
      m->velocity_y = 0; // On arrête le saut
    }
  }
  return 0;
}


void bloc_au_dessus(monstre *m, monde monde){
  int yMondeAuDessusTete = (m->y)/TAILLE_BLOCS+2;

  int xMonde = ((m->x)/TAILLE_BLOCS);
  int xMondeMid = ((m->x + (LARGEUR_MONSTRE/2))/TAILLE_BLOCS);
  int xMondeDroite = ((m->x + LARGEUR_MONSTRE-1)/TAILLE_BLOCS);

  if(estSolide(monde.grilleInt[TMONDE - yMondeAuDessusTete][xMonde]) ||
  estSolide(monde.grilleInt[TMONDE - yMondeAuDessusTete][xMondeMid]) ||
  estSolide(monde.grilleInt[TMONDE - yMondeAuDessusTete][xMondeDroite])){
    m->x -= m->velocity_x;
    m->y -= m->velocity_y;
    m->velocity_x = 0;
    m->velocity_y = 0; // On arrête le saut
    m->saut = 0;
  }
}


void pseudo_IA_monstre(monstre *m, character joueur){
  //On incrémente la variable et après avoir atteint une certaine valeur on fait sauter le slime
  m->calculSaut += 1;
  if(m->calculSaut >= 500 && m->calculSaut < 502){ // Il faut deux frames pour que le monstre saute
    if(m->calculSaut == 501){
      m->calculSaut = 0;
    }
    if(m->x > joueur.xMonde + joueur.pos.x){
      m->saut = GAUCHE;
    }else{
      m->saut = DROITE;
    }
  }else{
    m->saut = IMMOBILE;
  }
}
