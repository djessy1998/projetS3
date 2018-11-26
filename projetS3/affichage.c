#include <SDL.h>
#include <SDL/SDL_ttf.h>
#include "fonction.h"

void affichage_monde(monde monde, character joueur1, SDL_Surface *terre, SDL_Surface *screen, SDL_Surface *casque, SDL_Surface *armure, SDL_Surface *tronc, SDL_Surface *abg, SDL_Surface *abd,SDL_Surface *basArb,SDL_Surface *topArb){
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
	  if(monde.affichage[i][j] == TOPARB){
	      SDL_Rect posGrille;
	      posGrille.x = j*TAILLE_BLOCS + decalageX;
	      posGrille.y = i*TAILLE_BLOCS + decalageY;
	      SDL_BlitSurface(topArb, NULL, screen, &posGrille);	  	
	  }
	  if(monde.affichage[i][j] == TERRE)
	    {
	      SDL_Rect posGrille;
	      posGrille.x = j*TAILLE_BLOCS + decalageX;
	      posGrille.y = i*TAILLE_BLOCS + decalageY;
	      SDL_BlitSurface(terre, NULL, screen, &posGrille);
	    }
	  if(monde.affichage[i][j] == CASQUE){
	      SDL_Rect posGrille;
	      posGrille.x = j*TAILLE_BLOCS + decalageX;
	      posGrille.y = i*TAILLE_BLOCS + decalageY - 7;
	      SDL_BlitSurface(casque, NULL, screen, &posGrille);
	  }
	  if(monde.affichage[i][j] == ARMURE){
	      SDL_Rect posGrille;
	      posGrille.x = j*TAILLE_BLOCS + decalageX;
	      posGrille.y = i*TAILLE_BLOCS + decalageY - 7;
	      SDL_BlitSurface(armure, NULL, screen, &posGrille);	  	
	  }
	  if(monde.affichage[i][j] == ARBRE){
	      SDL_Rect posGrille;
	      posGrille.x = j*TAILLE_BLOCS + decalageX;
	      posGrille.y = i*TAILLE_BLOCS + decalageY;
	      SDL_BlitSurface(tronc, NULL, screen, &posGrille);		  	
	  }
	  if(monde.affichage[i][j] == ABG){
	      SDL_Rect posGrille;
	      posGrille.x = j*TAILLE_BLOCS + decalageX;
	      posGrille.y = i*TAILLE_BLOCS + decalageY;
	      SDL_BlitSurface(abg, NULL, screen, &posGrille);		  	
	  }
	  if(monde.affichage[i][j] == ABD){
	      SDL_Rect posGrille;
	      posGrille.x = j*TAILLE_BLOCS + decalageX;
	      posGrille.y = i*TAILLE_BLOCS + decalageY;
	      SDL_BlitSurface(abd, NULL, screen, &posGrille);		  	
	  }
	  if(monde.affichage[i][j] == BASARB){
	      SDL_Rect posGrille;
	      posGrille.x = j*TAILLE_BLOCS + decalageX;
	      posGrille.y = i*TAILLE_BLOCS + decalageY;
	      SDL_BlitSurface(basArb, NULL, screen, &posGrille);	  	
	  }
	}
    }
}


void affichage_items_inv(input input, SDL_Surface *casque, SDL_Surface *armure, SDL_Surface *screen, SDL_Surface *terre){
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
      else if(input.data.typeMemoire == 3){
	  SDL_BlitSurface(terre, NULL, screen, &input.data.posImage);
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

void affichage_barre_inv(SDL_Surface *invIm, SDL_Surface *screen, input *input, SDL_Surface *casque, SDL_Surface *armure, SDL_Surface *Actuel, SDL_Surface *terre, int *choixAct){
	int i;
	SDL_Rect posBarInv;
	SDL_Rect posBarItInv;
	SDL_Rect ActInv;
	SDL_Rect posTexte;
	SDL_Surface *nomItem;
  	TTF_Font *police = NULL;
  	police = TTF_OpenFont("Polices/angelina.ttf", 35);
  	SDL_Color couleurNoire = {0, 0, 0};
	for(i=0;i<10;i++){
	posBarInv.x = 2 + (31*i);
	posBarInv.y = 33;
	SDL_BlitSurface(invIm, NULL, screen, &posBarInv);
	posBarItInv.x = 2 + (31 * i) + 2;
	posBarItInv.y = 37;
		  if(input->data.inv[0][i].type == 1)
		    {
		      SDL_BlitSurface(casque, NULL, screen, &posBarItInv);
		    }
		  else if(input->data.inv[0][i].type == 2)
		    {
		      SDL_BlitSurface(armure, NULL, screen, &posBarItInv);
		    }
		  else if(input->data.inv[0][i].type == 3){
		      SDL_BlitSurface(terre, NULL, screen, &posBarItInv);		    
		  }
	}
	if(input->data.e == 0){
		if(input->data.Un == 1){
			ActInv.x = 2;
			ActInv.y = 33;
			posTexte.x = 2;
			posTexte.y = 64;
			nomItem = TTF_RenderText_Solid (police,input->data.inv[0][0].nomItem, couleurNoire);
			*choixAct = input->data.inv[0][0].type;
		}
		else if(input->data.Deux == 1){
			ActInv.x = 33;
			ActInv.y = 33;
			posTexte.x = 33;
			posTexte.y = 64;
			nomItem = TTF_RenderText_Solid (police,input->data.inv[0][1].nomItem, couleurNoire);
			*choixAct = input->data.inv[0][1].type;
		}
		else if(input->data.Trois == 1){
			ActInv.x = 64;
			ActInv.y = 33;
			posTexte.x = 64;
			posTexte.y = 64;
			nomItem = TTF_RenderText_Solid (police,input->data.inv[0][2].nomItem, couleurNoire);
			*choixAct = input->data.inv[0][2].type;
		}
		else if(input->data.Quatre == 1){
			ActInv.x = 95;
			ActInv.y = 33;
			posTexte.x = 95;
			posTexte.y = 64;
			nomItem = TTF_RenderText_Solid (police,input->data.inv[0][3].nomItem, couleurNoire);
			*choixAct = input->data.inv[0][3].type;
		}
		else if(input->data.Cinq == 1){
			ActInv.x = 126;
			ActInv.y = 33;
			posTexte.x = 126;
			posTexte.y = 64;
			nomItem = TTF_RenderText_Solid (police,input->data.inv[0][4].nomItem, couleurNoire);
			*choixAct = input->data.inv[0][4].type;
		}
		else if(input->data.Six == 1){
			ActInv.x = 157;
			ActInv.y = 33;
			posTexte.x = 157;
			posTexte.y = 64;
			nomItem = TTF_RenderText_Solid (police,input->data.inv[0][5].nomItem, couleurNoire);
			*choixAct = input->data.inv[0][5].type;
		}
		else if(input->data.Sept == 1){
			ActInv.x = 188;
			ActInv.y = 33;
			posTexte.x = 188;
			posTexte.y = 64;
			nomItem = TTF_RenderText_Solid (police,input->data.inv[0][6].nomItem, couleurNoire);
			*choixAct = input->data.inv[0][6].type;
		}
		else if(input->data.Huit == 1){
			ActInv.x = 219;
			ActInv.y = 33;
			posTexte.x = 219;
			posTexte.y = 64;
			nomItem = TTF_RenderText_Solid (police,input->data.inv[0][7].nomItem, couleurNoire);
			*choixAct = input->data.inv[0][7].type;
		}
		else if(input->data.Neuf == 1){
			ActInv.x = 250;
			ActInv.y = 33;
			posTexte.x = 250;
			posTexte.y = 64;
			nomItem = TTF_RenderText_Solid (police,input->data.inv[0][8].nomItem, couleurNoire);
			*choixAct = input->data.inv[0][8].type;
		}
		else if(input->data.Dix == 1){
			ActInv.x = 281;
			ActInv.y = 33;
			posTexte.x = 281;
			posTexte.y = 64;
			nomItem = TTF_RenderText_Solid (police,input->data.inv[0][9].nomItem, couleurNoire);
			*choixAct = input->data.inv[0][9].type;
		}
		SDL_BlitSurface(nomItem, NULL, screen, &posTexte);
		SDL_BlitSurface(Actuel, NULL, screen, &ActInv);
	}
	TTF_CloseFont(police);
}

void affichage_crack(monde *monde, int *incAnim, SDL_Surface *Crack, SDL_Surface *screen, int minaX, int minaY, character *a) {
  int StartFen = TMONDE - a->yMonde/TAILLE_BLOCS - NBBLOCS_FENETREY;
  SDL_Rect posCrack;
  posCrack.x = (minaX*TAILLE_BLOCS - a->xMonde);
  posCrack.y = (((minaY - StartFen))*16) - 2;
  SDL_Rect crackAnim;
  crackAnim.x = 15;
  crackAnim.y = 0;
  crackAnim.h = 15;
  crackAnim.w = 15;
  if(*incAnim > 15 && *incAnim < 30){
    crackAnim.y = 15;
    SDL_BlitSurface(Crack, &crackAnim, screen, &posCrack);
  }
  else if(*incAnim > 30 && *incAnim < 45){
    crackAnim.y = 30;
    SDL_BlitSurface(Crack, &crackAnim, screen, &posCrack);
  }
  else if(*incAnim >= 45 && *incAnim < 60){
    crackAnim.y = 35;
    SDL_BlitSurface(Crack, &crackAnim, screen, &posCrack);
  }
}
