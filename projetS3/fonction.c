#include "fonction.h"
#include <SDL.h>
#include <math.h>

void deplacerG(character *a, float *vitesse, int murGau, int *murDro)
{
  if(murGau == 0 && *murDro == 0)
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

void sauter(character *a, double vx, double *vy, double *vgrav)
{
	a->xMonde += vx;
	a->yMonde += *vy;
	*vy -= *vgrav;
	if (a->yMonde <= 160)
	{
		*vy = 4;
		*vgrav = 0.08;
	}
}

void baisser(character *a)
{
  
}

void gravite(character *a, float *force)
{
	a->yMonde -= 1;
}

void collision(character *a, int affichage[NBBLOCS_FENETREY][NBBLOCS_FENETREX], float *force, int *bloquerG, int *bloquerD, int posB[TMONDE][TMONDE], int posBY[TMONDE][TMONDE])
{
	int touche = 0;
	int i,j;
	int posGrilleX = (int)(round((a->pos.x)/TAILLE_BLOCS));
	int posGrilleY = (int)(round((a->pos.y + PLAYER_HEIGHT)/TAILLE_BLOCS));
	float JpiedGX = a->xMonde + a->pos.x;
	float JMilieuX = a->xMonde + a->pos.x + PLAYER_WIDTH/2;
	float JpiedDX = a->xMonde + a->pos.x + PLAYER_WIDTH;
	float JpiedGY = a->yMonde;
	printf("JpiedGY = %f\n", JpiedGY);
	printf("posBY[25][21] = %d\n", posBY[25][21]);
    for(i = 0; i < NBBLOCS_FENETREY; i++)
    {
       for(j = 0; j< NBBLOCS_FENETREX; j++)
       {
       		if(affichage[i][j] == TERRE)
       		{
       			if(((JpiedGX >= posB[i][j] && JpiedGX <= posB[i][j] + TAILLE_BLOCS) || (JpiedDX >= posB[i][j] && JpiedDX <= posB[i][j] + TAILLE_BLOCS)) && JpiedGY == posBY[i][j])
       			{
       				touche = 1;
       				break;
       			}
       		}
       }
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
