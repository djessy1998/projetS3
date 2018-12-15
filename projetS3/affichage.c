#include <SDL.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include "fonction.h"
#include "creator.h"
#include "constant.h"

void affichage_fond(atlas *atlasJeu, SDL_Surface *screen){
  SDL_BlitSurface(atlasJeu->tabIm[BG_IM]->surface, NULL, screen, &atlasJeu->tabIm[BG_IM]->pos);
}

void affichage_monde(monde monde, character joueur1, atlas* atlasJeu, SDL_Surface *screen){
  int xAffichageStart = joueur1.xMonde/TAILLE_BLOCS;
  int yAffichageStart = TMONDE - joueur1.yMonde/TAILLE_BLOCS - NBBLOCS_FENETREY;
  int decalageX = -joueur1.xMonde%TAILLE_BLOCS;
  int decalageY = joueur1.yMonde%TAILLE_BLOCS;
  for(int i=0;i<NBBLOCS_FENETREY;i++ ){
    for(int j=0;j<NBBLOCS_FENETREX;j++){
  	  monde.affichage[i][j] = monde.grilleInt[i+yAffichageStart][j+xAffichageStart];
  	  monde.posB[i][j] = TAILLE_BLOCS*(j+xAffichageStart);
  	  monde.posBY[i][j] = TAILLE_BLOCS*(joueur1.yMonde/TAILLE_BLOCS + NB_BLOCS_AU_DESSUS_JOUEUR - i);
  	  SDL_Rect posGrille;
  	  posGrille.x = j*TAILLE_BLOCS + decalageX;
  	  posGrille.y = i*TAILLE_BLOCS + decalageY;
      switch (monde.affichage[i][j]){
        case VIDE:
          break;
    	  case TOPARB:
    		  posGrille.x = j*TAILLE_BLOCS + decalageX - 33;
    		  posGrille.y = i*TAILLE_BLOCS + decalageY - 64;
    	    SDL_BlitSurface(atlasJeu->tabIm[TOPARB_IM]->surface, NULL, screen, &posGrille);
          break;
        case CASQUE:
    	    if(estGrotte(monde.affichage[i-(i>0)][j])){
    	      SDL_BlitSurface(atlasJeu->tabIm[FONDTERRE1_IM]->surface, NULL, screen, &posGrille);
    	      posGrille.x += TAILLE_BLOCS;
    	      SDL_BlitSurface(atlasJeu->tabIm[FONDTERRE1_IM]->surface, NULL, screen, &posGrille);
    	      posGrille.x -= TAILLE_BLOCS;
            j++; // On passe l'affichage de la case de fond de grotte (sinon elle passe au dessus de l'objet)
    	    }
    	    posGrille.y = i*TAILLE_BLOCS + decalageY - 7;
    	    SDL_BlitSurface(atlasJeu->tabIm[CASQUE_IM]->surface, NULL, screen, &posGrille);
          break;
        case ARMURE:
    	    if(estGrotte(monde.affichage[i-(i>0)][j])){
    	      SDL_BlitSurface(atlasJeu->tabIm[FONDTERRE1_IM]->surface, NULL, screen, &posGrille);
    	      posGrille.x += TAILLE_BLOCS;
    	      SDL_BlitSurface(atlasJeu->tabIm[FONDTERRE1_IM]->surface, NULL, screen, &posGrille);
    	      posGrille.x -= TAILLE_BLOCS;
            j++; // On passe l'affichage de la case de fond de grotte (sinon elle passe au dessus de l'objet)
    	    }
    	    posGrille.y = i*TAILLE_BLOCS + decalageY - 7;
    	    SDL_BlitSurface(atlasJeu->tabIm[ARMURE_IM]->surface, NULL, screen, &posGrille);
          break;
        default:
          SDL_BlitSurface(atlasJeu->tabIm[monde.affichage[i][j]]->surface, NULL, screen, &posGrille);
          break;
      }
  	}
  }
}

void affichage_items_inv(input input, atlas* atlasJeu, SDL_Surface *screen){
  if(input.data.numItemInvX != -1 && input.data.rien == 0){
    if(input.data.typeMemoire == 1){
  	  SDL_BlitSurface(atlasJeu->tabIm[CASQUEINV_IM]->surface, NULL, screen, &input.data.posImage);
  	}else if(input.data.typeMemoire == 2){
  	  SDL_BlitSurface(atlasJeu->tabIm[ARMUREINV_IM]->surface, NULL, screen, &input.data.posImage);
  	}else if(input.data.typeMemoire == 3){
      SDL_BlitSurface(atlasJeu->tabIm[TERREINV_IM]->surface, NULL, screen, &input.data.posImage);
    }
  }
}

void affichage_personnage(character *joueur1, atlas* atlasJeu, SDL_Surface *screen){
  SDL_Rect posTexte;
  posTexte.x = joueur1->pos.x - 10;
  posTexte.y = joueur1->pos.y - 15;
  TTF_Font *police = NULL;
  SDL_Surface *nomJ;
  SDL_Color couleurNoire = {0, 0, 0};
  police = TTF_OpenFont("Polices/angelina.ttf", 25);
  nomJ = TTF_RenderText_Solid (police,joueur1->nom, couleurNoire);
  if(joueur1->mort == 0){
    SDL_BlitSurface(nomJ, NULL, screen, &posTexte);
    if(joueur1->dir == 2){
    	if(joueur1->invinc <= 500){
    	  if(joueur1->compt > 20){
    	    SDL_BlitSurface(atlasJeu->tabIm[JOUEURD_IM]->surface,&atlasJeu->tabIm[JOUEURD_IM]->anim, screen, &joueur1->pos);
    	    joueur1->compt = 0;
    	  }
    	}else{
    	  SDL_BlitSurface(atlasJeu->tabIm[JOUEURD_IM]->surface,&atlasJeu->tabIm[JOUEURD_IM]->anim, screen, &joueur1->pos);
    	}
    }else if(joueur1->dir == 1){
    	if(joueur1->invinc <= 500){
    	  if(joueur1->compt > 20){
    	    SDL_BlitSurface(atlasJeu->tabIm[JOUEUR_IM]->surface, &atlasJeu->tabIm[JOUEUR_IM]->anim, screen, &joueur1->pos);
    	    joueur1->compt = 0;
    	  }
    	}else{
    	  SDL_BlitSurface(atlasJeu->tabIm[JOUEUR_IM]->surface, &atlasJeu->tabIm[JOUEUR_IM]->anim, screen, &joueur1->pos);
    	}
    }
    joueur1->compt += 1;
  }
  SDL_FreeSurface(nomJ);
  TTF_CloseFont(police);
}

void affichage_vie_personnage(character *a, atlas* atlasJeu, SDL_Surface *screen){
  int i;
  if(a->PV%10 == 0){
    for(i = 0; i < a->PV/10; i++){
      setPosX(atlasJeu->tabIm[VIEENT_IM],i*30 + 1);
      setPosY(atlasJeu->tabIm[VIEENT_IM], 2);
      SDL_BlitSurface(atlasJeu->tabIm[VIEENT_IM]->surface, NULL, screen, &atlasJeu->tabIm[VIEENT_IM]->pos);
    }
    for(i = a->PV/10; i < 10;i++){
      setPosX(atlasJeu->tabIm[NOVIE_IM],i*30 + 1);
      setPosY(atlasJeu->tabIm[NOVIE_IM], 2);
      SDL_BlitSurface(atlasJeu->tabIm[NOVIE_IM]->surface, NULL, screen, &atlasJeu->tabIm[NOVIE_IM]->pos);
    }
  }
  if(a->PV%5 == 0 && a->PV%10 != 0){
    for(i = 0;i<= (a->PV - 5)/10;i++){
      setPosX(atlasJeu->tabIm[VIEENT_IM], i*30 + 1);
      setPosY(atlasJeu->tabIm[VIEENT_IM], 2);
      SDL_BlitSurface(atlasJeu->tabIm[VIEENT_IM]->surface, NULL, screen, &atlasJeu->tabIm[VIEENT_IM]->pos);
    }
    SDL_BlitSurface(atlasJeu->tabIm[MIVIE_IM]->surface, NULL, screen, &atlasJeu->tabIm[VIEENT_IM]->pos);
    for(i = (a->PV + 5)/10; i < 10;i++){
      setPosX(atlasJeu->tabIm[MIVIE_IM],i*30 + 1);
      setPosY(atlasJeu->tabIm[MIVIE_IM], 2);
      SDL_BlitSurface(atlasJeu->tabIm[NOVIE_IM]->surface, NULL, screen, &atlasJeu->tabIm[MIVIE_IM]->pos);
    }
  }
}

void affichage_vie_monstre(monstre *monstre, atlas* atlasJeu, SDL_Surface *screen, character *a){
  int i;
  if(monstre->mort != 1){
    if((monstre->x > a->xMonde && monstre->x < a->xMonde + SCREEN_WIDTH) && (monstre->y > a->yMonde && monstre->y < a->yMonde + SCREEN_HEIGHT)){
      if(monstre->PV%10 == 0){
        for(i = 0; i < monstre->PV/10; i++){
          setPosX(atlasJeu->tabIm[VIEENTM_IM],(monstre->pos.x - 3) + i*18 + 1);
          setPosY(atlasJeu->tabIm[VIEENTM_IM], monstre->pos.y - 18);
          SDL_BlitSurface(atlasJeu->tabIm[VIEENTM_IM]->surface, NULL, screen, &atlasJeu->tabIm[VIEENTM_IM]->pos);
        }
        for(i = monstre->PV/10; i < 2 ;i++){
          setPosX(atlasJeu->tabIm[NOVIEM_IM],(monstre->pos.x - 3) + i*18 + 1);
          setPosY(atlasJeu->tabIm[NOVIEM_IM], monstre->pos.y - 18);
          SDL_BlitSurface(atlasJeu->tabIm[NOVIEM_IM]->surface, NULL, screen, &atlasJeu->tabIm[NOVIEM_IM]->pos);
        }
      }
      if(monstre->PV%5 == 0 && monstre->PV%10 != 0){
        for(i = 0;i<= (monstre->PV - 5)/10;i++){
          setPosX(atlasJeu->tabIm[VIEENTM_IM],(monstre->pos.x - 3) + i*18 + 1);
          setPosY(atlasJeu->tabIm[VIEENTM_IM], monstre->pos.y - 18);
          SDL_BlitSurface(atlasJeu->tabIm[VIEENTM_IM]->surface, NULL, screen, &atlasJeu->tabIm[VIEENTM_IM]->pos);
        }
        SDL_BlitSurface(atlasJeu->tabIm[MIVIEM_IM]->surface, NULL, screen, &atlasJeu->tabIm[VIEENTM_IM]->pos);
        for(i = (monstre->PV + 5)/10; i < 2 ;i++){
          setPosX(atlasJeu->tabIm[MIVIEM_IM],(monstre->pos.x - 3) + i*18 + 1);
          setPosY(atlasJeu->tabIm[MIVIEM_IM], monstre->pos.y - 18);
          SDL_BlitSurface(atlasJeu->tabIm[NOVIEM_IM]->surface, NULL, screen, &atlasJeu->tabIm[MIVIEM_IM]->pos);
        }
      }
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
  	SDL_BlitSurface(atlasJeu->tabIm[INVIM_IM]->surface, NULL, screen, &posBarInv);
  	posBarItInv.x = 6 + (31 * i) + 2;
  	posBarItInv.y = 38;
	  if(input->data.inv[0][i].type == 1){
	      SDL_BlitSurface(atlasJeu->tabIm[CASQUEINV_IM]->surface, NULL, screen, &posBarItInv);
    }else if(input->data.inv[0][i].type == 2){
      SDL_BlitSurface(atlasJeu->tabIm[ARMUREINV_IM]->surface, NULL, screen, &posBarItInv);
    }else if(input->data.inv[0][i].type == 3){
	    SDL_BlitSurface(atlasJeu->tabIm[TERREINV_IM]->surface, NULL, screen, &posBarItInv);
	  }
	}
	if(input->data.e == 0){
	  ActInv.x = ((input->data.clavier - 1)*31) + 2;
		ActInv.y = 33;
		posTexte.x = ((input->data.clavier - 1)*31) + 2;
		posTexte.y = 64;
		nomItem = TTF_RenderText_Solid (police,input->data.inv[0][input->data.clavier-1].nomItem, couleurNoire);
		*choixAct = input->data.inv[0][input->data.clavier-1].type;
		SDL_BlitSurface(nomItem, NULL, screen, &posTexte);
		SDL_BlitSurface(atlasJeu->tabIm[ACTUELINV_IM]->surface, NULL, screen, &ActInv);
		SDL_FreeSurface(nomItem);
	}
	TTF_CloseFont(police);
}

void affichage_crack(monde *monde, int *incAnim, atlas* atlasJeu, character *a, SDL_Surface *screen) {
  int StartFen = TMONDE - a->yMonde/TAILLE_BLOCS - NBBLOCS_FENETREY;
  setPosX(atlasJeu->tabIm[CRACK_IM], a->minaX*TAILLE_BLOCS - a->xMonde);
  setPosY(atlasJeu->tabIm[CRACK_IM], (a->minaY - StartFen)*16 - 2);
  if(*incAnim > 15 && *incAnim < 30){
    setAnimY(atlasJeu->tabIm[CRACK_IM], 15);
    SDL_BlitSurface(atlasJeu->tabIm[CRACK_IM]->surface, &atlasJeu->tabIm[CRACK_IM]->anim, screen, &atlasJeu->tabIm[CRACK_IM]->pos);
  }else if(*incAnim > 30 && *incAnim < 45){
    setAnimY(atlasJeu->tabIm[CRACK_IM], 30);
    SDL_BlitSurface(atlasJeu->tabIm[CRACK_IM]->surface, &atlasJeu->tabIm[CRACK_IM]->anim, screen, &atlasJeu->tabIm[CRACK_IM]->pos);
  }else if(*incAnim >= 45 && *incAnim < 60){
    setAnimY(atlasJeu->tabIm[CRACK_IM], 45);
    SDL_BlitSurface(atlasJeu->tabIm[CRACK_IM]->surface, &atlasJeu->tabIm[CRACK_IM]->anim, screen, &atlasJeu->tabIm[CRACK_IM]->pos);
  }
}

void affichage_monstre(monstre *monstre, atlas* atlasJeu, SDL_Surface *screen, character joueur){
  if(monstre->mort == 0){
    if(monstre->x > joueur.xMonde && monstre->x < joueur.xMonde + SCREEN_WIDTH && monstre->y > joueur.yMonde && monstre->y < joueur.yMonde + SCREEN_HEIGHT){
      monstre->pos.x = monstre->x - joueur.xMonde;
      monstre->pos.y = NBBLOCS_FENETREY*TAILLE_BLOCS - (monstre->y - joueur.yMonde);
      SDL_BlitSurface(atlasJeu->tabIm[SLIME_IM]->surface, &atlasJeu->tabIm[SLIME_IM]->anim, screen, &monstre->pos);
    }
  }
}

void affichage_nuage(atlas* atlasJeu, SDL_Surface *screen, int choix[4], double *posxR, int *nbR, int *boo){
  srand(time(NULL));
  int i = 0;
  if(*boo == 0){
    for(i=0;i< *nbR;i++){
      int nbRa = rand()%(CLOUD3_IM - CLOUD1_IM + 1) + CLOUD_IM;
      choix[i] = nbRa;
      setPosX(atlasJeu->tabIm[choix[i]], 0);
      setPosY(atlasJeu->tabIm[choix[i]], atlasJeu->tabIm[TOPARB_IM]->pos.y + rand()%(300));
    }
    *boo = 1;
  }
  for(i=0;i< *nbR;i++){
    if(choix[i] > CLOUD3_IM || choix[i] < CLOUD_IM){
      choix[i] = CLOUD1_IM;
    }
    if(atlasJeu->tabIm[choix[i]]->pos.x > SCREEN_WIDTH + 300){
      *nbR = rand()%(5-1) + 1;
      *posxR = 0;
      *boo = 0;
    }else{
      *posxR += 0.2;
      setPosX(atlasJeu->tabIm[choix[i]], (int)*posxR);
      SDL_BlitSurface(atlasJeu->tabIm[choix[i]]->surface,NULL, screen, &atlasJeu->tabIm[choix[i]]->pos);
    }
  }
}


void affichage_mini_map(monde *monde, character *joueur, atlas *atlasJeu, SDL_Surface *screen){
  SDL_Surface *miniMap = creer_minimap(monde, joueur);

  SDL_Rect posMiniMap;

  posMiniMap.x = SCREEN_WIDTH - 208  - 10;
  posMiniMap.y = 18;
  posMiniMap.h = 100;
  posMiniMap.w = 100;

  SDL_BlitSurface(miniMap, NULL, screen, &posMiniMap);

  SDL_FreeSurface(miniMap);

  SDL_BlitSurface(atlasJeu->tabIm[MAP_IM]->surface, NULL, screen, &atlasJeu->tabIm[MAP_IM]->pos);
}
