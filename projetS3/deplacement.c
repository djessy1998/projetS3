#include "fonction.h"
#include <SDL.h>
#include <math.h>


void deplacerG(character *a, int murGau, int murDro)
{
  if(murGau == 0 && murDro == 0)
    {
      a->xMondeDouble =  a->xMondeDouble - VITESSE;
      a->xMonde = (int)a->xMondeDouble;
      a->xPosBloquageDouble = a->pos.x;
    }
  else
    {
      a->xPosBloquageDouble = a->xPosBloquageDouble - VITESSE;
      a->pos.x = (int)a->xPosBloquageDouble;
    }
}


void deplacerD(character *a, int murDro, int murGau)
{
  if(murDro == 0 && murGau == 0)
    {
      a->xMondeDouble =  a->xMondeDouble + VITESSE;
      a->xMonde = (int)a->xMondeDouble;
      a->xPosBloquageDouble = a->pos.x;
    }
  else
    {
      a->xPosBloquageDouble = a->xPosBloquageDouble + VITESSE;
      a->pos.x = (int)a->xPosBloquageDouble;
    }
}


void sauter(character *a)
{
  if(a->autorisationSaut){
    if(a->velocity_y > 20){
      a->velocity_y = 20;
      a->autorisationSaut = 0;
    }else if(a->velocity_y <= -1){ //Si le joueur reste enfoncé sur la touche et que velocity_y va trop loin
      a->velocity_y = 0;
      a->autorisationSaut = 0;
    }else{
      a->velocity_y -= 1;
    }
    if(a->yMonde < TMONDE*16 - NBBLOCS_FENETREY*TAILLE_BLOCS){
      a->yMondeDouble += (double)a->velocity_y;
    }else{
      a->yPosBloquageDouble -=  a->velocity_y;
      a->pos.y = (int) a->yPosBloquageDouble;
    }
    a->yMonde = (int)round(a->yMondeDouble);
  }
}


void baisser(character *a)
{

}
