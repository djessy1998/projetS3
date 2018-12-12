#include "fonction.h"
#include "creator.h"
#include <SDL.h>
#include <math.h>

void construction(monde *monde, input *input, character *a, int *choixAct, int *minaX, int *minaY){
  int posJY = TMONDE - ((a->yMonde + (NBBLOCS_FENETREY*TAILLE_BLOCS - a->pos.y) - PLAYER_HEIGHT)/16);
  int posJX = (a->xMonde + a->pos.x)/16;
  int jb,ib,i,j,trouve = 0;
  if(*choixAct == 3){
    if((monde->grilleInt[*minaY][*minaX] == VIDE || monde->grilleInt[*minaY][*minaX] == FONDGROTTE) && input->data.butDown == 1 && abs(*minaX - posJX) < LIMITEMINA && abs(*minaY - posJY) < LIMITEMINA){
     monde->grilleInt[*minaY][*minaX] = TERRESH;
      for(i=0;i<4;i++){
	for(j=0;j<10;j++){
	  if(input->data.inv[i][j].type == 3){
	   jb = j;
	   ib = i;
	   trouve = 1;
	   break;
	  }
	}
	if(trouve == 1){
	 break;
	}
      }
     input->data.inv[ib][jb].type = -1;
     input->data.inv[ib][jb].nomItem = " ";
     *choixAct = 0;
    }
  }
}
