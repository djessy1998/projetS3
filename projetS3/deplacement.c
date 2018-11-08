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
  a->x_saut += 1.;
  if ((a->x_saut) >= -140.)
    {
      a->x_saut = -154;
      a->autorisationSaut = 0;
      a->y_saut = 0;
    }
  else{
    a->y_saut = -0.0001* (a->x_saut) * (a->x_saut) + 24;
    if(a->yMonde >= TMONDE*16 - (37*16) - 10)
      {
	a->yMonde = TMONDE*16 - (37*16) - 10;
	a->pos.y -= (int)a->y_saut;
      }
    else
      {
	a->pos.y = 346;
	a->yMonde += (int)a->y_saut;
      }
  }
}


void baisser(character *a)
{

}
