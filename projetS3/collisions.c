#include "fonction.h"
#include "creator.h"
#include <SDL.h>
#include <math.h>

void gravite(character *a)
{
  if(a->yMonde >= TMONDE*16 - NBBLOCS_FENETREY*TAILLE_BLOCS && a->pos.y < 346){ //Valeur ou le personnage est au centre en Y
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

void collision(character *a, int** affichage, int** posB, int** posBY, int *murDr, int *yMomTom, int *fait, int *faitCalc, int *yMomTomDeb, int *touche)
{
  a->bloqADroite = 0;
  a->bloqAGauche = 0;
  int i,j;
  int JpiedGX = a->xMonde + a->pos.x;
  int JMilieuX = a->xMonde + a->pos.x + PLAYER_WIDTH/2;
  int JpiedDX = a->xMonde + a->pos.x + PLAYER_WIDTH;
  int JpiedGY = a->yMonde+ (NBBLOCS_FENETREY*TAILLE_BLOCS - a->pos.y) - PLAYER_HEIGHT;
  *touche = 0;

  for(i = 0; i < NBBLOCS_FENETREY; i++)
    {
      for(j = 0; j< NBBLOCS_FENETREX; j++)
	{
	  if(affichage[i][j] == TERRE)
	    {
	      if(JpiedDX == posB[i][j])
		{
		  a->bloqADroite = 1;
		}
	      else if(JpiedGX == posB[i][j] + TAILLE_BLOCS)
		{
		  a->bloqAGauche = 1;
		}
	      if(((JpiedGX > posB[i][j] && JpiedGX < posB[i][j] + TAILLE_BLOCS) ||
        (JpiedDX > posB[i][j] && JpiedDX <= posB[i][j] + TAILLE_BLOCS) ||
        (JMilieuX > posB[i][j] && JMilieuX < posB[i][j] + TAILLE_BLOCS)) &&
        JpiedGY == TAILLE_BLOCS * (a->yMonde / TAILLE_BLOCS + NBBLOCS_FENETREY - i))
		{
		  *touche = 1;
		  a->autorisationSaut = 1;
		  a->sautH = 0;
		  a->velocity_y = 20;
		  break;
		}
	    }
	}
    }


  int PosPiedY = (a->pos.y/16) +1;
  int PosCorpsY = (a->pos.y/16 +2);
  int PosTeteY = (a->pos.y/16) +3;
  int PosPiedX;
  //Bug sur le mur droit, le joueur allait trop loin
  if(*murDr){
    PosPiedX = a->pos.x/16-1;
  }
  else{
    PosPiedX = a->pos.x/16;
  }
  int PosPiedDX = a->pos.x/16 + PLAYER_WIDTH/16 +1 ;

  if((affichage[PosPiedY][PosPiedX] == VIDE &&
      affichage[PosCorpsY][PosPiedX] == VIDE &&
      affichage[PosTeteY][PosPiedX] == VIDE)) {
    a->bloqAGauche=0;
  }

  if((affichage[PosPiedY][PosPiedDX] == VIDE &&
      affichage[PosCorpsY][PosPiedDX] == VIDE &&
      affichage[PosTeteY][PosPiedDX] == VIDE)){
    a->bloqADroite=0;
  }
  
  //Si bloc au dessus du joueur.
  if(affichage[a->pos.y/16][a->pos.x/16+1] == TERRE ||
    affichage[a->pos.y/16][a->pos.x/16+2] == TERRE){
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
