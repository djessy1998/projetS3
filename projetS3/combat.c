#include <SDL.h>
#include <SDL/SDL_ttf.h>
#include "fonction.h"
#include "creator.h"
#include "constant.h"

void combat(monstre *m, character *a, monde monde, input *input){
  if(m->coupPr < 0){
    m->coupPr = 500;
  }
  //Calcule des positions x et y joueur/monstre
  int yMondeMo = (m->y - HAUTEUR_MONSTRE)/TAILLE_BLOCS;
  int xMondeMo = m->x/TAILLE_BLOCS;
  int xMondeJ = (a->xMonde + a->pos.x)/16;
  int yMondeJ = (((a->yMonde + (NBBLOCS_FENETREY*TAILLE_BLOCS - a->pos.y) - PLAYER_HEIGHT)/16));
  if((((yMondeMo - 1 >= yMondeJ - 3  && yMondeMo - 1 <= yMondeJ)) && (xMondeMo == xMondeJ))){
    //Si le joueur n'est plus invincible (Si il ne c'est pas fait touché pendant x secondes)
    if(a->invinc > 500){
    	if(m->dernierSaut == GAUCHE){
    	  a->xMondeDouble =  a->xMondeDouble - 20;
    	  a->xMonde = (int)a->xMondeDouble;
    	}else if(m->dernierSaut == DROITE){
    	  a->xMondeDouble =  a->xMondeDouble + 20;
    	  a->xMonde = (int)a->xMondeDouble;
    	}
    	a->PV = a->PV - 10;
    	a->invinc = 0;
    }
  }
  if(a->invinc <= 500){
     a->invinc += 1./(double)NBMONSTRE;
  }
  if((a->minaX-1 == xMondeMo && a->minaY - 1 == TMONDE - yMondeMo - 2) && input->data.butDown == 1){
    if(m->coupPr > 100){
      if(m->mort == 0){
        m->PV -= a->degatM;
        if(m->PV == 0){
          m->mort = 1;
        }
        m->coupPr = 0;
      }
    }
  }
  if(m->coupPr <= 500){
    m->coupPr += 1;
  }
}

void game_over(character *a, monde monde, SDL_Surface *screen, int *inc, input *input){
  if(a->PV == 0){
    //*inc sert à laisser l'écran sur "You were slain ..." quelques temps puis on fait réapparaitre le joueur
    if(*inc < 300){
      a->mort = 1;
      SDL_Rect posTexte;
      SDL_Surface *motMort;
      TTF_Font *police = NULL;
      police = TTF_OpenFont("Polices/Andy.ttf", 50);
      SDL_Color couleurNoire = {0, 0, 0};
      posTexte.x = SCREEN_WIDTH/2 - 120;
      posTexte.y = SCREEN_HEIGHT/2;
      motMort = TTF_RenderText_Blended (police,"You were slain ..." , couleurNoire);
      SDL_BlitSurface(motMort, NULL, screen, &posTexte);
      TTF_CloseFont(police);
      SDL_FreeSurface(motMort);
    }else{
      apparition_joueur(a,monde);
      //On vide l'inventaire quand le joueur meurt
      for(int i = 0; i < 4; i++){
        for(int j = 0; j < 10; j++){
            input->data.inv[i][j].type = -1;
            input->data.inv[i][j].nomItem = "";
        }
      }
      a->mort = 0;
      a->PV = 100;
      *inc = 0;
    }
    *inc += 1;
 }
}
