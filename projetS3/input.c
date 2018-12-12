#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include "touches.h"
#include <SDL.h>
#include <math.h>


void fonction_Handle_Event(SDL_Event event, input *input, character *a, monde *monde,int *incAnim, int *minaX, int *minaY, int *choixAct){
  switch (event.type) {
    /* close button clicked */
  case SDL_QUIT:
    quit(input);
    break;
  case SDL_MOUSEBUTTONDOWN:
    Mouse_Down(event, input);
    construction(monde, input, a, choixAct, minaX,minaY);
    break;
  case SDL_MOUSEBUTTONUP:
    Mouse_Up(event, input);
    break;
  case SDL_MOUSEMOTION:
    Mouse_Motion(event, input, a, monde, incAnim, minaX, minaY);
    break;
  case SDL_KEYDOWN:
    /*printf("%d\n", event.key.keysym.scancode); Si l'on a besoin de retrouver le code d'une touche */
    switch (event.key.keysym.scancode) {
    case ECHAP:
      quit(input);
      break;
    case Z:
      input->data.z = 1;
      break ;
    case Q:
      input->data.q = 1;
      break;
    case S:
      input->data.s = 1;
      break;
    case D:
      input->data.d = 1;
      break;
    case E: // e
      if(input->data.e == 0)
	{
	  input->data.e = 1;
	  SDL_Delay(80);
	}
      else
	{
	  input->data.e = 0;
	  SDL_Delay(80);
	 }
    break;
    case F: // f
      input->data.f = 1;
      break;
    case ESPER: // &
      input->data.clavier = 1;
      break;
    case EACC: // é
      input->data.clavier = 2;
      break;
    case DOUBLEQUOTE: // ""
      input->data.clavier = 3;
      break;
    case QUOTE: // ''
      input->data.clavier = 4;
      break;
    case LEFTPAREN: // (
      input->data.clavier = 5;
      break;
    case TIRET: // -
      input->data.clavier = 6;
      break;
    case EACCGRA: // è
      input->data.clavier = 7;
      break;
    case UNDERSCORE:// _
      input->data.clavier = 8;
      break;
    case CCEDILLE: // ç
      input->data.clavier = 9;
      break;
    case AACCENT: // à
      input->data.clavier = 10;
      break;
    default:
      break;
    }
    break;
  case SDL_KEYUP:
    switch(event.key.keysym.sym){
    case SDLK_z:
      input->data.z = 0;
      break;
    case SDLK_q:
      input->data.q = 0;
      break;
    case SDLK_s:
      input->data.s = 0;
      break;
    case SDLK_d:
      input->data.d = 0;
      break;
    case SDLK_f:
      input->data.f = 0;
      break;
    default:
      break;
    }
    break;
  }
}

void quit(input *input){
  input->data.quit = 1;
}

void Mouse_Down(SDL_Event event, input *input){
  if (event.button.button == SDL_BUTTON_LEFT)
    {
      input->data.butDown = 1;
    }
}

void Mouse_Up(SDL_Event event, input *input){
  if (event.button.button == SDL_BUTTON_LEFT)
    {
      input->data.butDown = 0;
    }
}

void Mouse_Motion(SDL_Event event, input *input, character *a, monde *monde,int *incAnim, int *minaX, int *minaY){
  for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 10; j++)
	{
	  if(((input->data.butDown == 1) && ((event.motion.x >= 2 + (31 * j) && event.motion.x <= 2 + 32 + (31 * j)) && (event.motion.y >= 33 + (31 * i) && event.motion.y <= 33 + 32 + (31 * i))) && (input->data.e == 1)))
	    {
	      if(input->data.getB == 0)
		{
		  input->data.numItemInvY = i;
		  input->data.numItemInvX = j;
		  input->data.getB = 1;
		}
	      if((input->data.butDown == 1) && input->data.inv[input->data.numItemInvY][input->data.numItemInvX].type == -2)
		{
		  input->data.inv[input->data.numItemInvY][input->data.numItemInvX].type = -1;
		  input->data.rien = 1;
		}
	      if(input->data.rien == 0)
		{
		  input->data.posImage.x = event.motion.x - 16;
		  input->data.posImage.y = event.motion.y - 16;
		}
	    }
	  if((input->data.butDown == 1) && ((event.motion.x <= 2 || event.motion.x >= 2 + 32) && (event.motion.y <= 33 || event.motion.y >= 33 + 32)) && (input->data.e == 1))
	    {
	      if(input->data.rien == 0)
		{
		  input->data.posImage.x = event.motion.x - 16;
		  input->data.posImage.y = event.motion.y - 16;
		}
	    }
	  if((input->data.butDown == 0) && ((event.motion.x >= 2 && event.motion.x <= 2 + (31 * 10)) && (event.motion.y >= 33 && event.motion.y <= 33 + (31 * 4))) && (input->data.e == 1))
	    {
	      if(input->data.numItemInvX != -1 && input->data.numItemInvY != -1)
		{
		  if(input->data.rien == 0)
		    {
		      TrierInv(input->data.rien, input->data.inv, input->data.typeMemoire);
		    }
		  input->data.numItemInvX = -1;
		  input->data.numItemInvY = -1;
		  input->data.supprimer = 0;
		  input->data.getB = 0;
		  input->data.rien = 0;
		}
	    }
	  else if((input->data.butDown == 0) && ((event.motion.x <= 2 || event.motion.x >= 2 + 32) && (event.motion.y <= 33 || event.motion.y >= 33 + 32)) && (input->data.e == 1))
	    {
	      if(input->data.numItemInvX != -1 && input->data.numItemInvY != -1)
		{
      input->data.inv[0][input->data.numItemInvX].nomItem = " ";
		  input->data.posImage.x = -300;
		  input->data.posImage.y = -300;
		  input->data.numItemInvX = -1;
		  input->data.numItemInvY = -1;
		  input->data.supprimer = 0;
		  input->data.getB = 0;
		}
	    }
	}
    }
  *minaX = (a->xMonde + event.motion.x)/16;
  *minaY = TMONDE - ((a->yMonde + (NBBLOCS_FENETREY*TAILLE_BLOCS - event.motion.y))/16) - 1;
}
