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
  int passage_yMonde_posy;
  if(a->autorisationSaut){
    if(a->velocity_y > VELOCITE_MAX){
      a->velocity_y = VELOCITE_MAX;
      a->autorisationSaut = 0;
    }else if(a->velocity_y > 0){
      a->velocity_y -= 1;
    }
    //Si le yMonde avec la vélocité vont trop loin alors on met yMonde au max et on enlève la diff entre yMonde et le maximum pour yMonde dans la velocité et ajoute la velocité restante dans pos.y
    if(a->yMonde + a->velocity_y > TMONDE*TAILLE_BLOCS - NBBLOCS_FENETREY*TAILLE_BLOCS){
      passage_yMonde_posy = a->yMonde + a->velocity_y - (TMONDE*TAILLE_BLOCS - NBBLOCS_FENETREY*TAILLE_BLOCS);
      a->yMondeDouble = TMONDE*TAILLE_BLOCS - NBBLOCS_FENETREY*TAILLE_BLOCS;
      a->yPosBloquageDouble -=  passage_yMonde_posy;
      a->pos.y = (int) a->yPosBloquageDouble;
    }else{
      if(a->yMonde < TMONDE*TAILLE_BLOCS - NBBLOCS_FENETREY*TAILLE_BLOCS){
	a->yMondeDouble += (double)a->velocity_y;
      }else{
	if(a->pos.y - a->velocity_y > 0){ //Plafond (non testé)
	  a->yPosBloquageDouble -=  a->velocity_y;
	}else{
	  a->yPosBloquageDouble = 0.;
	}
	a->pos.y = (int) a->yPosBloquageDouble;
      }
    }
    a->yMonde = (int)round(a->yMondeDouble);
  }
}


void baisser(character *a)
{

}
