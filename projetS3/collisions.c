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

void collision(character *a, int** affichage, int** posB, int** posBY, int *murDr, int *murGa, int *yMomTom, int *fait, int *faitCalc, int *yMomTomDeb, int *touche)
{
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
      if(estSolide(affichage[i][j])){
        if(JpiedDX == posB[i][j]){
          a->bloqADroite = 1;
        }else if(JpiedGX == posB[i][j] + TAILLE_BLOCS){
          a->bloqAGauche = 1;
        }

        if(((JpiedGX > posB[i][j] && JpiedGX < posB[i][j] + TAILLE_BLOCS) ||
        (JpiedDX > posB[i][j] && JpiedDX < posB[i][j] + TAILLE_BLOCS) ||
        (JMilieuX > posB[i][j] && JMilieuX < posB[i][j] + TAILLE_BLOCS)) &&
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

  int PosPiedDX = ((a->pos.x+PLAYER_WIDTH)/TAILLE_BLOCS) +1 - *murDr;
  int PosPiedGX = (a->pos.x/TAILLE_BLOCS) - *murDr;

  if(!estSolide(affichage[PosPiedY][PosPiedGX]) &&
      !estSolide(affichage[PosCorpsY][PosPiedGX]) &&
      !estSolide(affichage[PosTeteY][PosPiedGX])){
    a->bloqAGauche=0;
  }

  if(!estSolide(affichage[PosPiedY][PosPiedDX]) &&
      !estSolide(affichage[PosCorpsY][PosPiedDX]) &&
      !estSolide(affichage[PosTeteY][PosPiedDX])){
    a->bloqADroite=0;
  }

  //Si bloc au dessus du joueur.
  if(estSolide(affichage[PosHautTeteY][PosPiedGX+1]) ||
    estSolide(affichage[PosHautTeteY][PosPiedDX - a->bloqADroite - *murGa])){
     a->autorisationSaut = 0;
  }

  if(a->pos.x >= (45*TAILLE_BLOCS) - PLAYER_WIDTH)
    {
      a->bloqADroite = 1;
    }
  else if(a->pos.x <= 0)
    {
      a->bloqAGauche = 1;
    }
  if (*touche == 0)
    {
	   if(*fait == 0){
		*yMomTomDeb = a->yMonde;
		*fait = 1;
	      }
    	gravite(a);
    }
    else if (*faitCalc == 1 && *fait == 1)
    {
     *fait = 0;
     *faitCalc = 0;
    }
}

void terreRonde(character *a, int *murDro, int *murGau)
{
  if(a->xMonde <= 1 && a->pos.x <= (45*TAILLE_BLOCS)/2)
    {
      *murGau = 1;
    }
  else if(a->xMonde + 16*45 >= TMONDE*TAILLE_BLOCS && a->pos.x >= (45*TAILLE_BLOCS)/2)
    {
      *murDro = 1;
    }
  else
    {
      a->pos.x = 360;
      *murGau = 0;
      *murDro = 0;
    }
}

int estSolide(int bloc){
  return bloc == TERRESH || bloc == TERRE || bloc == TERRE1 || bloc == TERRE2 || bloc == TERRE3 || bloc == TERREHERBE1 || bloc == TERREHERBE2 || bloc == TERREHERBE3;
}

int estVide(int bloc){
  return bloc == VIDE || bloc == FONDGROTTE;
}
