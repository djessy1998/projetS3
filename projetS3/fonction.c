#include "fonction.h"
#include <SDL.h>
#include <math.h>

void deplacerG(character *a, float *vitesse, int murGau, int *murDro)
{
  if(murGau == 0 && *murDro == 0 )
  	{
   		*vitesse =  *vitesse - VITESSE;
  		a->xMonde = (int)*vitesse;
  	}
  	else
    {
  		a->pos.x -= 1;
  	}
}

void deplacerD(character *a, float *vitesse, int murDro, int *murGau)
{
  if(murDro == 0 && *murGau == 0)
  	{
   		*vitesse =  *vitesse + VITESSE;
  		a->xMonde = (int)*vitesse;
  	}
  	else
    {
  		a->pos.x += 1;
    }
}

void sauter(character *a, double *PosRelJoueur1X, double *PosRelJoueur1Y, int Default)
{
	*PosRelJoueur1X += VITESSE;
	*PosRelJoueur1Y += (0.00001*(*PosRelJoueur1X)*(*PosRelJoueur1X))+10;
	a->xMonde = a->xMonde + *PosRelJoueur1X;
	a->yMonde = a->yMonde + *PosRelJoueur1Y;
	printf("%d\n", a->yMonde);
	if(a->yMonde > Default + 50)
	{
	  *PosRelJoueur1X = 0;
	  *PosRelJoueur1Y = Default;
	}
}

void baisser(character *a)
{
  
}

void gravite(character *a, float *force)
{
	a->yMonde -= 1;
}

void collision(character *a, int affichage[NBBLOCS_FENETREY][NBBLOCS_FENETREX], float *force, int *bloquerG, int *bloquerD, int posB[NBBLOCS_FENETREY][NBBLOCS_FENETREX - 2], int LastDir)
{   
    int qwerty = 0;
	int touche = 0;
	int posGrilleX = (int)(((a->pos.x)/TAILLE_BLOCS)) + LastDir;
	int posGrilleY = (int)(((a->pos.y + PLAYER_HEIGHT)/TAILLE_BLOCS));
	int posGrilleXMilieu =(int)(((a->pos.x+PLAYER_WIDTH/2)/TAILLE_BLOCS)) + LastDir;
	int posGrilleXDroite =(int)(((a->pos.x+PLAYER_WIDTH)/TAILLE_BLOCS)) + LastDir;
	
	if(affichage[posGrilleY][posGrilleX] ||  affichage[posGrilleY][posGrilleXMilieu] || affichage[posGrilleY][posGrilleXDroite])
	  {
	    touche = 1;
	  }
	if(posB[posGrilleY-1][posGrilleX] + TAILLE_BLOCS == a->pos.x)
	  {
	    *bloquerG = 1;
	  }
	else if(posB[posGrilleY-1][posGrilleX + 2] == a->pos.x + PLAYER_WIDTH)
	  {
	    *bloquerD = 1;
	  }
	if(a->pos.x >= (45*TAILLE_BLOCS) - PLAYER_WIDTH)
	  {
	  	*bloquerD = 1;
	  }
	else if(a->pos.x <= 0)
	  {
	  	*bloquerG = 1;
	  }
	else
	  {
	    *bloquerG = 0;
	    *bloquerD = 0;
	  }

	if (touche == 0)
	{
		gravite(a, force);
	}
}

void terreRonde(int *xMondeBl, character *a, int *murDro, int *murGau)
{
	if(a->xMonde <= 1 && a->pos.x <= (45*TAILLE_BLOCS)/2)
	{
		*murGau = 1;
	}
	else if(a->xMonde + 16*45 >= TMONDE*16 && a->pos.x >= (45*TAILLE_BLOCS)/2)
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
