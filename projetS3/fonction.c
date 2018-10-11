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

void sauter(character *a, int *saut, float *x, float *y, int murDro, int murGau)
{
  *x += 0.00001;
  *y += 0.0002* (*x) * (*x);
  if (!murDro && !murGau){ 
      a->xMonde += *x + 50;
      a->yMonde += (int)*y;
  }
  else{
  }
  if (*y > 8.)
  {
    *y = 0.;
    *x = -50.;
    *saut = 0;
  }
}

void baisser(character *a)
{
  
}

void gravite(character *a, float *force)
{
	a->yMonde -= 1;
}

void collision(character *a, int affichage[NBBLOCS_FENETREY][NBBLOCS_FENETREX], float *force, int *bloquerG, int *bloquerD, int posB[TMONDE][TMONDE], int posBY[TMONDE][TMONDE], int *saut)
{
	int touche = 0;
	*bloquerD = 0;
	*bloquerG = 0;
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
       			if(((JpiedGX > posB[i][j] && JpiedGX < posB[i][j] + TAILLE_BLOCS) || (JpiedDX > posB[i][j] && JpiedDX <= posB[i][j] + TAILLE_BLOCS) || (JMilieuX > posB[i][j] && JMilieuX < posB[i][j] + TAILLE_BLOCS)) && JpiedGY == posBY[i][j])
       			{
       				touche = 1;
					*saut = 1;
       				break;
       			}
       			if(JpiedGY < posBY[i][j] && JpiedDX == posB[i][j])
       			{
       				*bloquerD = 1;
       			}
       			else if(JpiedGY < posBY[i][j] && JpiedGX == posB[i][j] + TAILLE_BLOCS)
       			{
       				*bloquerG = 1;
       			}
       		}
       }
    } 

	if(a->pos.x >= (45*TAILLE_BLOCS) - PLAYER_WIDTH)
	  {
	  	*bloquerD = 1;
	  }
	else if(a->pos.x <= 0)
	  {   
	  	*bloquerG = 1;
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

Liste *initialisation()
{
    Liste *liste = malloc(sizeof(*liste));
    items *EItems = malloc(sizeof(*EItems));
    if (liste == NULL || EItems == NULL)
    {
        exit(EXIT_FAILURE);
    }
    EItems->type = -1;
    EItems->xMondeItem = -1;
    EItems->yMondeItem = -1;
    EItems->suivant = NULL;
    liste->premier = EItems;
    return liste;
}

void insertion(Liste *liste, int nvType, int nvXMonde, int nvYMonde)
{
    items *nouveau = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->type = nvType;
    nouveau->xMondeItem = nvXMonde;
    nouveau->yMondeItem = nvYMonde;
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}

void suppression(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    if (liste->premier != NULL)
    {
        items *aSupprimer = liste->premier;
        liste->premier = liste->premier->suivant;
        free(aSupprimer);
    }
}

//pour le debuguage
void afficherListe(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    items *actuel = liste->premier;
    while (actuel != NULL)
    {
        printf("%d -> ", actuel->type);
        actuel = actuel->suivant;
    }
    printf("NULL\n");
}

void TrierInv(int rienI, items inv[4][10], int type)
{
  int o, p = 0;
  int trouve = 0;
      if(rienI == 0)
      {
        while(trouve == 0 && o < 4)
          {
           while(trouve == 0)
            {
             if(inv[o][p].type == -1)
              {
                inv[o][p].type = type;
		            trouve = 1;   
              }
              p = p + 1;
            }
            o = o + 1;
          }
          o = 0;
          p = 0;
      } 
}

int RegarderSiPlaceLig(items inv[4][10])
{
  int o, p = 0;
  int trouve = 0;
  int res = 0;
  while(trouve == 0 && o < 4)
    {
      while(trouve == 0)
        {
          if(inv[o][p].type == -1)
           {
            res = 0;
            trouve = 1;   
           }
            p = p + 1;
        }
        o = o + 1;
    }
  o = 0;
  p = 0;
  return res;

} 

int RegarderSiPlaceCol(items inv[4][10])
{
  int o, p = 0;
  int trouve = 0;
  int res = 0;
  while(trouve == 0 && o < 4)
    {
      while(trouve == 0)
        {
          if(inv[o][p].type == -1)
           {
            res = p;
            trouve = 1;
          }
            p = p + 1;
        }
        o = o + 1;
    }
  o = 0;
  p = 0;
  return res;
} 