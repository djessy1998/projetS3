#include "fonction.h"
#include <SDL.h>
#include <math.h>

void gravite(character *a)
{
  if((int)round(a->yMondeDouble)%2 == 1){
    a->yMondeDouble -= 1.;
  }else{
    a->yMondeDouble -= 2.;
  }
  a->yMonde = (int)round(a->yMondeDouble);
}

void collision(character *a, int** affichage, int** posB, int** posBY, int *murDr)
{
  int touche = 0;
  a->bloqADroite = 0;
  a->bloqAGauche = 0;
  int i,j;
  int JpiedGX = a->xMonde + a->pos.x;
  int JMilieuX = a->xMonde + a->pos.x + PLAYER_WIDTH/2;
  int JpiedDX = a->xMonde + a->pos.x + PLAYER_WIDTH;
  int JpiedGY = a->yMonde;

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
	      if(((JpiedGX > posB[i][j] && JpiedGX < posB[i][j] + TAILLE_BLOCS) || (JpiedDX > posB[i][j] && JpiedDX <= posB[i][j] + TAILLE_BLOCS) || (JMilieuX > posB[i][j] && JMilieuX < posB[i][j] + TAILLE_BLOCS)) && JpiedGY == posBY[i][j])
		{
		  touche = 1;
		  a->autorisationSaut = 1;
		  a->sautH = 0;
		  a->y_saut = 0;
		  a->x_saut = 0;
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

  if(a->pos.x >= (45*TAILLE_BLOCS) - PLAYER_WIDTH)
    {
      a->bloqADroite = 1;
    }
  else if(a->pos.x <= 0)
    {
      a->bloqAGauche = 1;
    }
  if (touche == 0)
    {
      if(a->yMonde >= TMONDE*16 - (37*16) - 10 && a->pos.y <= 346)
	{
	  a->pos.y+=1;
	}
      else
	{
	  a->pos.y = 346;
	  gravite(a);
	}
    }
}

void terreRonde(character *a, int *murDro, int *murGau, int *murHau)
{
  if(a->yMonde >= TMONDE*16 - (37*16))
    {
      *murHau = 1;
    }
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
      *murHau = 0;
    }
}
