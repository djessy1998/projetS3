#include "fonction.h"
#include <SDL.h>
#include <math.h>

void deplacerG(character *a, int murGau, int murDro)
{
  if(murGau == 0 && murDro == 0)
    {
      a->xMondeDouble =  a->xMondeDouble - VITESSE;
      a->xMonde = (int)a->xMondeDouble;
      a->xPosBloquageDouble = a->pos.x;
    }
  else
    {
      a->xPosBloquageDouble = a->xPosBloquageDouble - VITESSE;
      a->pos.x = (int)a->xPosBloquageDouble;
    }
}

void deplacerD(character *a, int murDro, int murGau)
{
  if(murDro == 0 && murGau == 0)
    {
      a->xMondeDouble =  a->xMondeDouble + VITESSE;
      a->xMonde = (int)a->xMondeDouble;
      a->xPosBloquageDouble = a->pos.x;
    }
    else
    {
      a->xPosBloquageDouble = a->xPosBloquageDouble + VITESSE;
      a->pos.x = (int)a->xPosBloquageDouble;
    }
}

void sauter(character *a, int *saut, int murDro, int murGau)
{
  a->x_saut += 1.;
  if ((a->x_saut) >= -140.)
  {
    a->x_saut = -154;
    *saut = 0;
    a->y_saut = 0;
  }
  else{
    a->y_saut = -0.0001* (a->x_saut) * (a->x_saut) + 24;
    if(a->yMonde >= TMONDE*16 - (37*16) - 10)
    {
      a->yMonde = TMONDE*16 - (37*16) - 10;
      a->pos.y -= (int)a->y_saut;
    }
    else
    {
      a->pos.y = 346;
      a->yMonde += (int)a->y_saut;
    }
  }
}

void baisser(character *a)
{

}

void gravite(character *a)
{
	a->yMonde -= 1;
}

void collision(character *a, int** affichage, int *bloquerG, int *bloquerD, int** posB, int** posBY, int *saut, int *murDr)
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
	    if(JpiedDX == posB[i][j])
	    {
	      *bloquerD = 1;
	    }
	    else if(JpiedGX == posB[i][j] + TAILLE_BLOCS)
	    {
	      *bloquerG = 1;
	    }
	    if(((JpiedGX > posB[i][j] && JpiedGX < posB[i][j] + TAILLE_BLOCS) || (JpiedDX > posB[i][j] && JpiedDX <= posB[i][j] + TAILLE_BLOCS) || (JMilieuX > posB[i][j] && JMilieuX < posB[i][j] + TAILLE_BLOCS)) && JpiedGY == posBY[i][j])
	    {
	      touche = 1;
	      *saut = 1;
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
      *bloquerG=0;
    }

    if((affichage[PosPiedY][PosPiedDX] == VIDE &&
      affichage[PosCorpsY][PosPiedDX] == VIDE &&
      affichage[PosTeteY][PosPiedDX] == VIDE)){
      *bloquerD=0;
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
// 	printf("a->yMonde = %d\n", a->yMonde);
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

void afficherElementsListe(Liste *liste, int *ItemAffich, int dirChar, character *a, SDL_Surface *screen, SDL_Surface *casque, SDL_Surface *armure, int q, int d, int bloqD, int bloqG)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    items *actuel = liste->premier;
    while (actuel != NULL)
    {
	if ((actuel->xMondeItem > a->xMonde && actuel->xMondeItem <= a->xMonde + SCREEN_WIDTH) || (actuel->xMondeItem + 28 < a->xMonde))
	{
	    actuel->boolean = 0;
	}
        if(actuel->xMondeItem >= a->xMonde && actuel->xMondeItem <= a->xMonde + SCREEN_WIDTH)
        {
          if(actuel->type == 1)
          {
            if(dirChar == 1)
            {
              actuel->posItemMonde.x = (int)actuel->avG;
              actuel->avD = actuel->avG;
            }
            else
            {
              actuel->posItemMonde.x = (int)actuel->avD;
              actuel->avG = actuel->avD;
            }
            actuel->posItemMonde.y = a->yMonde + 248;
            SDL_BlitSurface(casque, NULL, screen, &actuel->posItemMonde);
            *ItemAffich = 1;
          }
          else if(actuel->type == 2)
          {
            if(dirChar == 1)
            {
              actuel->posItemMonde.x = (int)actuel->avG;			// A FACTORISER EN RAJOUTANT UN SDL_SURFACE DANS LA STRUCTURE
              actuel->avD = actuel->avG;
            }
            else
            {
              actuel->posItemMonde.x = (int)actuel->avD;
              actuel->avG = actuel->avD;
            }
            actuel->posItemMonde.y = a->yMonde + 248;
            SDL_BlitSurface(armure, NULL, screen, &actuel->posItemMonde);
            *ItemAffich = 1;
          }
        }
        else
        {
	  if(actuel->xMondeItem + 28 > a->xMonde)
	  {
	   if(actuel->boolean == 0)
	   {
	    actuel->SortImPos.x = 0;
	    actuel->SortImPos.y = a->yMonde + 248;
	    if(actuel->xMondeItem <= a->xMonde && dirChar == 1)
	    {
	      actuel->increment = 28;
	    }
	    else if (actuel->xMondeItem + 28 < a->xMonde)
	    {
	      actuel->increment = 0;
	    }
	    actuel->SortIm.x = 28;
	    actuel->SortIm.y = 0;
	    actuel->SortIm.h = 24;
	    actuel->SortIm.w = 28;
	    actuel->boolean = 1;
	   }
	   else
	   {
	    actuel->SortImPos.y = a->yMonde + 248;
	    if(q == 1 && bloqD == 0 && bloqG == 0)
	    {
	      actuel->increment -= 0.09;
	      actuel->SortIm.x = (int)actuel->increment;
	      if(actuel->SortIm.x < 0)
	      {
			actuel->SortIm.x = 0;
	      }
	    }
	    if(d == 1 && bloqD == 0 && bloqG == 0)
	    {
	      actuel->increment += 0.09;
	      actuel->SortIm.x = (int)actuel->increment;

	      if(actuel->SortIm.x > 28)
	      {
			actuel->SortIm.x = 28;
	      }
	      if(actuel->increment > 28)
	      {
	      	actuel->increment = 28;
	      }
	    }
	     if(actuel->type == 1)
	     {
	     	SDL_BlitSurface(casque, &actuel->SortIm , screen, &actuel->SortImPos);
	     }
	     if(actuel->type == 2)
	     {
	     	SDL_BlitSurface(armure, &actuel->SortIm , screen, &actuel->SortImPos);
	     }
	   }
	  }
          actuel->avD = 0;
          actuel->avG = 0;
        }
      actuel = actuel->suivant;
    }
}

void collisionItems(Liste *liste, int dirChar, int ItemAffich, int bloquerG, int bloquerD, character *a, int gauche, int droite, int murG, int murD)
{
  items *actuel = liste->premier;
  while (actuel != NULL)
  {
    if(droite == 1)
    {
      if(actuel->xMondeItem >= a->xMonde && actuel->xMondeItem <= a->xMonde + SCREEN_WIDTH)
        {
          if(ItemAffich == 1)
          {
            if(dirChar == 1)
            {
              actuel->avD = actuel->avG;
            }
            if(bloquerD == 0 && murD == 0 && murG == 0 && bloquerG == 0)
            {
              actuel->avD -= VITESSE;
            }
         }
        }
    }
    else if(gauche == 1)
    {
       if(actuel->xMondeItem >= a->xMonde && actuel->xMondeItem <= a->xMonde + SCREEN_WIDTH)
        {
          if(ItemAffich == 1)
          {
            if(dirChar == 2)
            {
              actuel->avG = actuel->avD;
            }
            if(bloquerG == 0 && murD == 0 && murG == 0 && bloquerD == 0)
            {
              actuel->avG += VITESSE;
            }
          }
        }
    }
    actuel = actuel->suivant;
  }
}
