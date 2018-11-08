#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"

void traitement_input(input input, character *joueur1, int murG, int murD, int gauche, int droite, Liste *listeItems, int ItemAffich, SDL_Rect *joueurAnimD, SDL_Rect *joueurAnim, int *incrim)
{
  if(input.data.z == 1)
    {
      if (joueur1->autorisationSaut)
      {
	SDL_Delay(10);
	sauter(joueur1);
      }
    }
  if(input.data.d == 1)
    {
      droite = 1;
      collisionItems(listeItems, ItemAffich, joueur1, gauche, droite, murG, murD);
      if(joueur1->bloqADroite == 0)
	{
	  deplacerD(joueur1, murD, murG);
	}
      *incrim += 2;
      if(*incrim > 58)
	{
	  joueurAnimD->y += 58;
	  *incrim = 0;
	}
      if (joueurAnimD->y > 800)
      {
	joueurAnimD->y = 0;
      }
      joueur1->dir = 2;
    }
  else
    {
      droite = 0;
      joueurAnimD->y = 0;
    }
  if(input.data.s == 1)
    {
      baisser(joueur1);
    }
  if(input.data.q == 1)
    {
      gauche = 1;
      collisionItems(listeItems, ItemAffich, joueur1, gauche, droite, murG, murD);
      if(joueur1->bloqAGauche == 0)
	{
	  deplacerG(joueur1,murG, murD);
	}
      *incrim += 2;
      if(*incrim > 58)
	{
	  joueurAnim->y += 58;
	  *incrim = 0;
	}
      if (joueurAnim->y > 800)
      {
	joueurAnim->y = 0;
      }
      joueur1->dir = 1;
    }
  else
    {
      gauche = 0;
      joueurAnim->y = 0;
    }
}