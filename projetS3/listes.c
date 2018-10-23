#include "fonction.h"
#include <stdio.h>
#include <stdlib.h>

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

void afficherElementsListe(Liste *liste, int *ItemAffich, character *a, SDL_Surface *screen, SDL_Surface *casque, SDL_Surface *armure, int q, int d)
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
            if(a->dir == 1)
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
            if(a->dir == 1)
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
	    if(actuel->xMondeItem <= a->xMonde && a->dir == 1)
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
	    if(q == 1 && a->bloqADroite == 0 && a->bloqAGauche == 0)
	    {
	      actuel->increment -= 0.09;
	      actuel->SortIm.x = (int)actuel->increment;
	      if(actuel->SortIm.x < 0)
	      {
			actuel->SortIm.x = 0;
	      }
	    }
	    if(d == 1 && a->bloqADroite == 0 && a->bloqAGauche == 0)
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

void collisionItems(Liste *liste, int ItemAffich, character *a, int gauche, int droite, int murG, int murD)
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
            if(a->dir == 1)
            {
              actuel->avD = actuel->avG;
            }
            if(a->bloqADroite == 0 && murD == 0 && murG == 0 && a->bloqAGauche == 0)
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
            if(a->dir == 2)
            {
              actuel->avG = actuel->avD;
            }
            if(a->bloqAGauche == 0 && murD == 0 && murG == 0 && a->bloqADroite == 0)
            {
              actuel->avG += VITESSE;
            }
          }
        }
    }
    actuel = actuel->suivant;
  }
}
