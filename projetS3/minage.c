#include "fonction.h"
#include "creator.h"
#include <SDL.h>
#include <math.h>

void minage(input *input, character *a, int minaY, int minaX, int *incAnim, monde *monde){
  int posJY = TMONDE - ((a->yMonde + (NBBLOCS_FENETREY*TAILLE_BLOCS - a->pos.y) - PLAYER_HEIGHT)/16);
  int posJX = (a->xMonde + a->pos.x)/16;
  int i,j;
  int ib, jb;
  int trouve = 0;
  if(monde->grilleInt[minaY][minaX] == TERRE && input->data.butDown == 1 && abs(minaX - posJX) < LIMITEMINA && abs(minaY - posJY) < LIMITEMINA){
    *incAnim += VITESSEMINA;
    if(*incAnim > 60){
      monde->grilleInt[minaY][minaX] = VIDE;
      monde->grilleInt[minaY][minaX] = FONDGROTTE;
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
      printf("ib = %d\n", ib);
      printf("jb = %d\n", jb);
      if(i < 4 || j+1 < 10){
	input->data.inv[ib][jb].type = 3;
	input->data.inv[ib][jb].nomItem = "Terre";
      }
    }
  }
  else{
   *incAnim = 0;
  }
  if(input->data.butDown == 0){
   *incAnim = 0; 
  }    
}