#include "fonction.h"
#include "creator.h"
#include <SDL.h>
#include <math.h>
#include "constant.h"

void minage(input *input, character *a, int *incAnim, monde *monde){
  int posJY = TMONDE - ((a->yMonde + (NBBLOCS_FENETREY*TAILLE_BLOCS - a->pos.y) - PLAYER_HEIGHT)/16);
  int posJX = (a->xMonde + a->pos.x)/16;
  int i,j;
  int ib, jb;
  int trouve = 0;
  //Condition pour voir ou il peut miner
  if(estSolide(monde->grilleInt[a->minaY][a->minaX]) && input->data.butDown == 1 && (abs(a->minaX - posJX) < LIMITEMINA && (abs(a->minaY - posJY) < LIMITEMINA || abs(a->minaY - (posJY - PLAYER_HEIGHT/TAILLE_BLOCS)) <= LIMITEMINA))){
    *incAnim += VITESSEMINA;
    if(*incAnim > 60){
      monde->grilleInt[a->minaY][a->minaX] = VIDE;
      monde->grilleInt[a->minaY][a->minaX] = rand()%(FONDTERRE3 - FONDTERRE1 + 1) + FONDTERRE1;
      if(monde->grilleInt[a->minaY-1][a->minaX] == HERBE || monde->grilleInt[a->minaY-1][a->minaX] == HERBE1){
        monde->grilleInt[a->minaY-1][a->minaX] = VIDE;
      }
      for(i=0;i<4;i++){
      	for(j=0;j<10;j++){
      	  if(input->data.inv[i][j].type == -1){
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
      if(i < 4 || j+1 < 10){
      	input->data.inv[ib][jb].type = 3;
      	input->data.inv[ib][jb].nomItem = "Terre";
      }
    }
  }else{
   *incAnim = 0;
  }
  if(input->data.butDown == 0){
   *incAnim = 0;
  }
}
