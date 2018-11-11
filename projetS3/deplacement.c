#include "fonction.h"
#include <SDL.h>


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
    // printf(" y=%f \n", a->y_saut);
    // printf(" x=%f \n", a->x_saut);
    // printf(" yM=%d \n", a->yMonde);
    if(a->y_saut >= 20){
      a->x_saut = 1;
      a->y_saut = 0;
      // a->autorisationSaut = 0;
    }else if(a->y_saut <= -1){
      a->x_saut = 0;
      a->y_saut = 0;
      a->autorisationSaut = 0;
    }else{
      if(a->x_saut){
        a->y_saut -= 1;
      }else{
        a->y_saut += 1;
      }
    }
    a->yMondeDouble += a->y_saut;
    a->yMonde = (int)a->yMondeDouble;
  }

  // a->x_saut += 1.;
  // a->sautH = 1;
  // if ((a->x_saut) >= -140.) //max saut
  //   {
  //     a->x_saut = -154;
  //     a->autorisationSaut = 0;
  //     a->y_saut = 0;
  //     a->sautH = -1;
  //   }
  // else{
  //   a->y_saut = -0.0001* (a->x_saut) * (a->x_saut) + 24;
  //   if(a->yMonde >= TMONDE*TAILLE_BLOCS - (NBBLOCS_FENETREY*TAILLE_BLOCS) - 10)
  //     {
	// a->yMonde = TMONDE*TAILLE_BLOCS - (NBBLOCS_FENETREY*TAILLE_BLOCS) - 10;
	// a->pos.y -= (int)a->y_saut;
  //     }
  //   else
  //     {
	// a->pos.y = 346;
	// a->yMonde += (int)a->y_saut;
  //     }
  // }
}


void baisser(character *a)
{

}
