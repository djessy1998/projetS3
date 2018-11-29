#include <SDL.h>
#include <SDL/SDL_ttf.h>
#include "fonction.h"
#include "creator.h"

void affichage_monde(monde monde, character joueur1, atlas* atlasJeu, SDL_Surface *screen){
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
	  SDL_Rect posGrille;
	  posGrille.x = j*TAILLE_BLOCS + decalageX;
	  posGrille.y = i*TAILLE_BLOCS + decalageY;
	  if(monde.affichage[i][j] == TOPARB){
		posGrille.x = j*TAILLE_BLOCS + decalageX - 33;
		posGrille.y = i*TAILLE_BLOCS + decalageY - 64;
	    SDL_BlitSurface(atlasJeu->topArb->surface, NULL, screen, &posGrille);	  	
	  }else if(monde.affichage[i][j] == TERRE){
	    SDL_BlitSurface(atlasJeu->terre->surface, NULL, screen, &posGrille);
	  }else if(monde.affichage[i][j] == CASQUE){
	    if(monde.affichage[i-(i>0)][j] == FONDGROTTE){
	      SDL_BlitSurface(atlasJeu->fond_grotte->surface, &atlasJeu->fond_grotte->anim, screen, &posGrille);
	      posGrille.x += TAILLE_BLOCS;
	      SDL_BlitSurface(atlasJeu->fond_grotte->surface, &atlasJeu->fond_grotte->anim, screen, &posGrille);
	      posGrille.x -= TAILLE_BLOCS;
	    }
	    posGrille.y = i*TAILLE_BLOCS + decalageY - 7;
	    SDL_BlitSurface(atlasJeu->casque->surface, NULL, screen, &posGrille);
	  }else if(monde.affichage[i][j] == ARMURE){
	    if(monde.affichage[i-(i>0)][j] == FONDGROTTE){
	      SDL_BlitSurface(atlasJeu->fond_grotte->surface, &atlasJeu->fond_grotte->anim, screen, &posGrille);
	      posGrille.x += TAILLE_BLOCS;
	      SDL_BlitSurface(atlasJeu->fond_grotte->surface, &atlasJeu->fond_grotte->anim, screen, &posGrille);
	      posGrille.x -= TAILLE_BLOCS;
	    }
	    posGrille.y = i*TAILLE_BLOCS + decalageY - 7;
	    SDL_BlitSurface(atlasJeu->armure->surface, NULL, screen, &posGrille);	  	
	  }else if(monde.affichage[i][j] == ARBRE){
	    SDL_BlitSurface(atlasJeu->tronc->surface, NULL, screen, &posGrille);		  	
	  }else if(monde.affichage[i][j] == ABG){
	    SDL_BlitSurface(atlasJeu->abg->surface, NULL, screen, &posGrille);		  	
	  }else if(monde.affichage[i][j] == ABD){
	    SDL_BlitSurface(atlasJeu->abd->surface, NULL, screen, &posGrille);		  	
	  }else if(monde.affichage[i][j] == BASARB){
	    SDL_BlitSurface(atlasJeu->basArb->surface, NULL, screen, &posGrille);	  	
	  }else if(monde.affichage[i][j] == FONDGROTTE  && monde.affichage[i][j-(int)(j>0)] != ARMURE && monde.affichage[i][j-(int)(j>0)] != CASQUE){
	    SDL_BlitSurface(atlasJeu->fond_grotte->surface,&atlasJeu->fond_grotte->anim, screen, &posGrille);
	  }
	}
  }
}

void affichage_items_inv(input input, atlas* atlasJeu, SDL_Surface *screen){
  if(input.data.numItemInvX != -1 && input.data.rien == 0)
    {
      if(input.data.typeMemoire == 1)
	{
	  SDL_BlitSurface(atlasJeu->casque->surface, NULL, screen, &input.data.posImage);
	}
      else if(input.data.typeMemoire == 2)
	{
	  SDL_BlitSurface(atlasJeu->armure->surface, NULL, screen, &input.data.posImage);
	}
      else if(input.data.typeMemoire == 3){
	  SDL_BlitSurface(atlasJeu->terre->surface, NULL, screen, &input.data.posImage);
      }
    }
}

void affichage_personnage(character joueur1, atlas* atlasJeu, SDL_Surface *screen){
  if(joueur1.dir == 2)
    {
      SDL_BlitSurface(atlasJeu->characterD->surface,&atlasJeu->characterD->anim, screen, &joueur1.pos);
    }
  else if(joueur1.dir == 1)
    {
      SDL_BlitSurface(atlasJeu->character->surface, &atlasJeu->character->anim, screen, &joueur1.pos); 
    }
}

void affichage_vie_personnage(character *a, atlas* atlasJeu, SDL_Surface *screen){
  int i;
  if(a->PV%10 == 0){
   for(i = 0; i < a->PV/10; i++){
    setPosX(atlasJeu->vieEnt,i*30 + 1);
    setPosY(atlasJeu->vieEnt, 2);
    SDL_BlitSurface(atlasJeu->vieEnt->surface, NULL, screen, &atlasJeu->vieEnt->pos);
   }
    for(i = a->PV/10; i < 10;i++){
     setPosX(atlasJeu->noVie,i*30 + 1);
     setPosY(atlasJeu->noVie, 2);
     SDL_BlitSurface(atlasJeu->noVie->surface, NULL, screen, &atlasJeu->noVie->pos);  
    }
  }
  if(a->PV%5 == 0 && a->PV%10 != 0){
    for(i = 0;i<= (a->PV - 5)/10;i++){
      setPosX(atlasJeu->vieEnt, i*30 + 1);
      setPosY(atlasJeu->vieEnt, 2);
      SDL_BlitSurface(atlasJeu->vieEnt->surface, NULL, screen, &atlasJeu->vieEnt->pos);      
    }
    SDL_BlitSurface(atlasJeu->miVie->surface, NULL, screen, &atlasJeu->vieEnt->pos);
    for(i = (a->PV + 5)/10; i < 10;i++){
      setPosX(atlasJeu->miVie,i*30 + 1);
      setPosY(atlasJeu->miVie, 2);
      SDL_BlitSurface(atlasJeu->noVie->surface, NULL, screen, &atlasJeu->miVie->pos);  
    }
  }
}

void affichage_barre_inv (input *input,int *choixAct, atlas* atlasJeu, SDL_Surface *screen){
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
	SDL_BlitSurface(atlasJeu->invIm->surface, NULL, screen, &posBarInv);
	posBarItInv.x = 2 + (31 * i) + 2;
	posBarItInv.y = 37;
		  if(input->data.inv[0][i].type == 1)
		    {
		      SDL_BlitSurface(atlasJeu->casque->surface, NULL, screen, &posBarItInv);
		    }
		  else if(input->data.inv[0][i].type == 2)
		    {
		      SDL_BlitSurface(atlasJeu->armure->surface, NULL, screen, &posBarItInv);
		    }
		  else if(input->data.inv[0][i].type == 3){
		    SDL_BlitSurface(atlasJeu->terre->surface, NULL, screen, &posBarItInv);		    
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
		SDL_BlitSurface(atlasJeu->ActuelInv->surface, NULL, screen, &ActInv);
	}
	TTF_CloseFont(police);
}

void affichage_crack(monde *monde, int *incAnim, atlas* atlasJeu, int minaX, int minaY, character *a, SDL_Surface *screen) {
  int StartFen = TMONDE - a->yMonde/TAILLE_BLOCS - NBBLOCS_FENETREY;
  setPosX(atlasJeu->Crack, minaX*TAILLE_BLOCS - a->xMonde);
  setPosY(atlasJeu->Crack, (minaY - StartFen)*16 - 2);
  if(*incAnim > 15 && *incAnim < 30){
    setAnimY(atlasJeu->Crack, 15);
    SDL_BlitSurface(atlasJeu->Crack->surface, &atlasJeu->Crack->anim, screen, &atlasJeu->Crack->pos);
  }
  else if(*incAnim > 30 && *incAnim < 45){
    setAnimY(atlasJeu->Crack, 30);
    SDL_BlitSurface(atlasJeu->Crack->surface, &atlasJeu->Crack->anim, screen, &atlasJeu->Crack->pos);
  }
  else if(*incAnim >= 45 && *incAnim < 60){
    setAnimY(atlasJeu->Crack, 45);
    SDL_BlitSurface(atlasJeu->Crack->surface, &atlasJeu->Crack->anim, screen, &atlasJeu->Crack->pos);
  }
}

void affichage_monstre(monstre *monstre, atlas* atlasJeu, SDL_Surface *screen, character joueur){
  if(monstre->x > joueur.xMonde && monstre->x < joueur.xMonde + SCREEN_WIDTH && monstre->y > joueur.yMonde && monstre->y < joueur.yMonde + SCREEN_HEIGHT){
    atlasJeu->Image_Monstre->pos.x = monstre->x - joueur.xMonde;
    atlasJeu->Image_Monstre->pos.y = NBBLOCS_FENETREY*TAILLE_BLOCS - (monstre->y - joueur.yMonde);
    SDL_BlitSurface(atlasJeu->Image_Monstre->surface, &atlasJeu->Image_Monstre->anim, screen, &atlasJeu->Image_Monstre->pos);
    
    //Le monstre fait un saut quand on le voit ()
    monstre->velocity_y = VELOCITE_MAX;
  }
}
