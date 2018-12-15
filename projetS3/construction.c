#include "fonction.h"
#include "creator.h"
#include <SDL.h>
#include <math.h>
#include "constant.h"

void construction(monde *monde, input *input, character *a, int *choixAct){
  int posJY = TMONDE - ((a->yMonde + (NBBLOCS_FENETREY*TAILLE_BLOCS - a->pos.y) - PLAYER_HEIGHT)/16);
  int posJX = (a->xMonde + a->pos.x)/16;
  int jb,ib,i,j,trouve = 0;
  if(*choixAct == 3){
    if((estVide(monde->grilleInt[a->minaY][a->minaX])) && input->data.butDown == 1 && abs(a->minaX - posJX) < LIMITEMINA && abs(a->minaY - posJY) < LIMITEMINA){
      monde->grilleInt[a->minaY][a->minaX] = TERRE1;
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
