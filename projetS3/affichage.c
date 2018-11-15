#include <SDL.h>
#include "fonction.h"


void affichage_monde(monde monde, character joueur1, SDL_Surface *terre, SDL_Surface *screen){
  int xAffichageStart = joueur1.xMonde/TAILLE_BLOCS;
  int yAffichageStart = TMONDE - joueur1.yMonde/TAILLE_BLOCS - NBBLOCS_FENETREY;
  int decalageX = -joueur1.xMonde%TAILLE_BLOCS;
  int decalageY = joueur1.yMonde%TAILLE_BLOCS;
  int i = 0;
  int j = 0;
  for(i=0;i<NBBLOCS_FENETREY;i++ )
    {
      for(j=0;j<NBBLOCS_FENETREX;j++)
	{
	  monde.affichage[i][j] = monde.grilleInt[i+yAffichageStart][j+xAffichageStart];
	  monde.posB[i][j] = TAILLE_BLOCS*(j+xAffichageStart);
	  monde.posBY[i][j] = TAILLE_BLOCS*(joueur1.yMonde/TAILLE_BLOCS + NB_BLOCS_AU_DESSUS_JOUEUR - i);
	  if(monde.affichage[i][j] == TERRE)
	    {
	      SDL_Rect posGrille;
	      posGrille.x = j*TAILLE_BLOCS + decalageX;
	      posGrille.y = i*TAILLE_BLOCS + decalageY;
	      SDL_BlitSurface(terre, NULL, screen, &posGrille);
	    }
	}
    }
}


void affichage_items_inv(input input, SDL_Surface *casque, SDL_Surface *armure, SDL_Surface *screen){
  if(input.data.numItemInvX != -1 && input.data.rien == 0)
    {
      if(input.data.typeMemoire == 1)
	{
	  SDL_BlitSurface(casque, NULL, screen, &input.data.posImage);
	}
      else if(input.data.typeMemoire == 2)
	{
	  SDL_BlitSurface(armure, NULL, screen, &input.data.posImage);
	}
    }
}

void affichage_personnage(character joueur1, SDL_Surface *characterD, SDL_Surface *character, SDL_Rect *joueurAnimD, SDL_Rect *joueurAnim, SDL_Surface *screen){
  if(joueur1.dir == 2)
    {
      SDL_BlitSurface(characterD, joueurAnimD, screen, &joueur1.pos);
    }
  else if(joueur1.dir == 1)
    {
      SDL_BlitSurface(character, joueurAnim, screen, &joueur1.pos); 
    }
}

void affichage_vie_personnage(character *a, SDL_Surface *vie, SDL_Surface *miVie, SDL_Surface *noVie, SDL_Surface *screen){
  int i;
  SDL_Rect posVie;
  if(a->PV%10 == 0){
   for(i = 0; i < a->PV/10; i++){
    posVie.x = i*30 + 1;
    posVie.y = 2;
    SDL_BlitSurface(vie, NULL, screen, &posVie);
   }
    for(i = a->PV/10; i < 10;i++){
      posVie.x = i*30 + 1;
      posVie.y = 2;
      SDL_BlitSurface(noVie, NULL, screen, &posVie);  
    }
  }
  if(a->PV%5 == 0 && a->PV%10 != 0){
    for(i = 0;i<= (a->PV - 5)/10;i++){
      posVie.x = i*30 + 1;
      posVie.y = 2;
      SDL_BlitSurface(vie, NULL, screen, &posVie);      
    }
    SDL_BlitSurface(miVie, NULL, screen, &posVie);
    for(i = (a->PV + 5)/10; i < 10;i++){
      posVie.x = i*30 + 1;
      posVie.y = 2;
      SDL_BlitSurface(noVie, NULL, screen, &posVie);  
    }
  }  
}
