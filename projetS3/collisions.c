#include "fonction.h"
#include "creator.h"
#include <SDL.h>
#include <math.h>

void gravite(character *a){
  if(((a->yMonde >= TMONDE*TAILLE_BLOCS - NBBLOCS_FENETREY*TAILLE_BLOCS && a->pos.y != POSY_START - PLAYER_HEIGHT) || a->yMonde <= 0 ) && /*Valeur ou le personnage est au centre en Y*/
      a->pos.y + PLAYER_HEIGHT != SCREEN_HEIGHT){
    if((int)round(a->yPosBloquageDouble)%2 == 1){
      a->yPosBloquageDouble += 1.;
    }else{
      a->yPosBloquageDouble += 2.;
    }
    a->pos.y = (int) a->yPosBloquageDouble;
  }else{
    if((int)round(a->yMondeDouble)%2 == 1){
      a->yMondeDouble -= 1.;
    }else{
      a->yMondeDouble -= 2.;
    }
    a->yMonde = (int)round(a->yMondeDouble);
  }
}

void collision(character *a, monde monde, int *yMomTom, int *fait, int *faitCalc, int *yMomTomDeb, int *touche){
  a->bloqADroite = 0;
  a->bloqAGauche = 0;
  int i,j;
  int JpiedGX = a->xMonde + a->pos.x;
  int JMilieuX = a->xMonde + a->pos.x + PLAYER_WIDTH/2;
  int JpiedDX = a->xMonde + a->pos.x + PLAYER_WIDTH;
  int JpiedGY = a->yMonde + (NBBLOCS_FENETREY*TAILLE_BLOCS - a->pos.y) - PLAYER_HEIGHT;
  *touche = 0;

  for(i = 0; i < NBBLOCS_FENETREY; i++){
    for(j = 0; j< NBBLOCS_FENETREX; j++){
      if(estSolide(monde.affichage[i][j])){
        if(JpiedDX == monde.posB[i][j]){
          a->bloqADroite = 1;
        }else if(JpiedGX == monde.posB[i][j] + TAILLE_BLOCS){
          a->bloqAGauche = 1;
        }

        if(((JpiedGX > monde.posB[i][j] && JpiedGX < monde.posB[i][j] + TAILLE_BLOCS) ||
        (JpiedDX > monde.posB[i][j] && JpiedDX < monde.posB[i][j] + TAILLE_BLOCS) ||
        (JMilieuX > monde.posB[i][j] && JMilieuX < monde.posB[i][j] + TAILLE_BLOCS)) &&
        JpiedGY == TAILLE_BLOCS * (a->yMonde / TAILLE_BLOCS + NBBLOCS_FENETREY - i)){
          *touche = 1;
          a->autorisationSaut = 1;
          a->sautH = 0;
          a->velocity_y = 20;
          break;
        }
      }
    }
  }

  int PosHautTeteY = a->pos.y/TAILLE_BLOCS;
  int PosPiedY = (a->pos.y/TAILLE_BLOCS) +1;
  int PosCorpsY = (a->pos.y/TAILLE_BLOCS) +2;
  int PosTeteY = (a->pos.y/TAILLE_BLOCS) +3;

  int PosPiedDX = ((a->pos.x+PLAYER_WIDTH)/TAILLE_BLOCS) +1 - a->murD;
  int PosPiedGX = (a->pos.x/TAILLE_BLOCS) - a->murD;

  if(!estSolide(monde.affichage[PosPiedY][PosPiedGX]) &&
      !estSolide(monde.affichage[PosCorpsY][PosPiedGX]) &&
      !estSolide(monde.affichage[PosTeteY][PosPiedGX])){
    a->bloqAGauche=0;
  }

  if(!estSolide(monde.affichage[PosPiedY][PosPiedDX]) &&
      !estSolide(monde.affichage[PosCorpsY][PosPiedDX]) &&
      !estSolide(monde.affichage[PosTeteY][PosPiedDX])){
    a->bloqADroite=0;
  }

  //Si bloc au dessus du joueur.
  if(estSolide(monde.affichage[PosHautTeteY][PosPiedGX+1]) ||
      estSolide(monde.affichage[PosHautTeteY][PosPiedDX - a->bloqADroite - a->murG])){
     a->autorisationSaut = 0;
  }

  if(a->pos.x >= ((NBBLOCS_FENETREX - 2)*TAILLE_BLOCS) - PLAYER_WIDTH){
    a->bloqADroite = 1;
  }else if(a->pos.x <= 0){
    a->bloqAGauche = 1;
  }
  if (*touche == 0){
    if(*fait == 0){
      *yMomTomDeb = a->yMonde;
      *fait = 1;
    }
    gravite(a);
  }else if(*faitCalc == 1 && *fait == 1){
   *fait = 0;
   *faitCalc = 0;
  }
}

void terreRonde(character *a){
  if(a->xMonde <= 1 && a->pos.x <= ((NBBLOCS_FENETREX - 2)*TAILLE_BLOCS)/2){
      a->murG = 1;
    }else if(a->xMonde + TAILLE_BLOCS*(NBBLOCS_FENETREX - 2) >= TMONDE*TAILLE_BLOCS && a->pos.x >= ((NBBLOCS_FENETREX - 2)*TAILLE_BLOCS)/2){
      a->murD = 1;
    }else{
      a->pos.x = SCREEN_WIDTH/2;
      a->murG = 0;
      a->murD = 0;
    }
}

int estSolide(int bloc){
  return bloc == TERRESH || bloc == TERRE || bloc == TERRE1 || bloc == TERRE2 || bloc == TERRE3 || bloc == TERREHERBE1 || bloc == TERREHERBE2 || bloc == TERREHERBE3;
}

int estVide(int bloc){
  return bloc == VIDE || bloc == FONDTERRE1 || bloc == FONDTERRE2 || bloc == FONDTERRE3 || bloc == HERBE || bloc == HERBE1;
}

int estGrotte(int bloc){
  return bloc == FONDTERRE1 || bloc == FONDTERRE2 || bloc == FONDTERRE3;
}
