#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"

void traitement_input(input input, character *joueur1, int murG, int murD, int gauche, int droite, Liste *listeItems, int ItemAffich, SDL_Rect *joueurAnimD, SDL_Rect *joueurAnim, int *incrim)
{
  if(input.data.z == 1)
    {
      collisionItems(listeItems, ItemAffich, joueur1, gauche, droite, murG, murD);
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


void traitement_input_inv(input *input, SDL_Surface *invIm, SDL_Surface *casque, SDL_Surface *armure, SDL_Surface *screen){
  SDL_Rect posInv;
  SDL_Rect posItemsInv;
  if(input->data.e == 1)
    {
      int i;
      int j;
      for(i = 0; i < 4; i++)
	{
	  for(j = 0; j < 10; j++)
	    {
	      posInv.x = 50 + (33 * j);
	      posInv.y = 50 + (33 * i);
	      
	      SDL_BlitSurface(invIm, NULL, screen, &posInv);
	      
	      if(input->data.numItemInvX != -1 && input->data.supprimer == 0 && input->data.inv[input->data.numItemInvY][input->data.numItemInvX].type != -1)
		{
		  input->data.typeMemoire = input->data.inv[input->data.numItemInvY][input->data.numItemInvX].type;
		  input->data.inv[input->data.numItemInvY][input->data.numItemInvX].type = -1;
		  input->data.supprimer = 1;
		}
	      else if (input->data.numItemInvX != -1 && input->data.supprimer == 0 && input->data.inv[input->data.numItemInvY][input->data.numItemInvX].type == -1)
		{
		  input->data.inv[input->data.numItemInvY][input->data.numItemInvX].type = -2;
		  input->data.supprimer = 1;
		}
	      if(input->data.inv[i][j].type > -1)
		{
		  posItemsInv.x = 50 + (33 * j) + 2;
		  posItemsInv.y = 50 + (33 * i) + 4;
		  if(input->data.inv[i][j].type == 1)
		    {
		      SDL_BlitSurface(casque, NULL, screen, &posItemsInv);
		    }
		  else if(input->data.inv[i][j].type == 2)
		    {
		      SDL_BlitSurface(armure, NULL, screen, &posItemsInv);
		    }
		}
	    }
	}
    }
  if(input->data.f == 1)
    {
      //RAMASSAGE ITEM
    }
}
