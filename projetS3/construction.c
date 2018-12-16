#include "fonction.h"
#include "creator.h"
#include <SDL.h>
#include <math.h>
#include "constant.h"

void construction(monde *monde, input *input, character *a, int *choixAct){
  //Calcule de la position du joueur en X et Y
  int posJY = TMONDE - ((a->yMonde + (NBBLOCS_FENETREY*TAILLE_BLOCS - a->pos.y) - PLAYER_HEIGHT)/16);
  int posJX = (a->xMonde + a->pos.x)/16;
  int jb,ib,i,j,trouve = 0;
  //Si il a choisis dans la TERRE
  if(*choixAct == 3){
    //On regarde si il toutes les conditions sont bonnes pour poser le bloc
    if((estVide(monde->grilleInt[a->minaY][a->minaX])) && input->data.butDown == 1 && (abs(a->minaX - posJX) < LIMITEMINA && (abs(a->minaY - posJY) < LIMITEMINA || abs(a->minaY - (posJY - PLAYER_HEIGHT/TAILLE_BLOCS)) <= LIMITEMINA))){
      if(a->minaX <= posJX-1 || a->minaX >= posJX + 2){
        //Puis on le pose au bon endroit
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
        //On supprime ensuite le bloc de TERRE dans l'inventaire
        input->data.inv[ib][jb].type = -1;
        input->data.inv[ib][jb].nomItem = " ";
        *choixAct = 0;
      }
    }
  }
}
