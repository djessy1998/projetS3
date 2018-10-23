#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include <SDL.h>


void quit(input *input);
void Mouse_Down(SDL_Event event, input *input);
void Mouse_Up(SDL_Event event, input *input);
void Mouse_Motion(SDL_Event event, input *input);


void fonction_Handle_Event(SDL_Event event, input *input){
  switch (event.type) {
    /* close button clicked */
  case SDL_QUIT:
    quit(input);
    break;
  case SDL_MOUSEBUTTONDOWN:
    Mouse_Down(event, input);
    break;
  case SDL_MOUSEBUTTONUP:
    Mouse_Up(event, input);
    break;
  case SDL_MOUSEMOTION:
    Mouse_Motion(event, input);
    break;
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
      quit(input);
      break;
    case SDLK_z:
      input->data.z = 1;
      break ;
    case SDLK_q:
      input->data.q = 1;
      break;
    case SDLK_s:
      input->data.s = 1;
      break;
    case SDLK_d:
      input->data.d = 1;
      break;
    case SDLK_e:
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
    case SDLK_f:
      input->data.f = 1;
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

void Mouse_Motion(SDL_Event event, input *input){
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      if(((input->data.butDown == 1) && ((event.motion.x >= 52 + (33 * j) && event.motion.x <= 52 + 32 + (33 * j)) && (event.motion.y >= 54 + (33 * i) && event.motion.y <= 54 + 32 + (33 * i))) && (input->data.e == 1)))
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
      if((input->data.butDown == 1) && ((event.motion.x <= 52 || event.motion.x >= 52 + 32) && (event.motion.y <= 54 || event.motion.y >= 54 + 32)) && (input->data.e == 1))
      {
        if(input->data.rien == 0)
        {
          input->data.posImage.x = event.motion.x - 16;
          input->data.posImage.y = event.motion.y - 16;
        }
      }
      if((input->data.butDown == 0) && ((event.motion.x >= 50 && event.motion.x <= 50 + (33 * 10)) && (event.motion.y >= 50 && event.motion.y <= 50 + (33 * 4))) && (input->data.e == 1))
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
      else if((input->data.butDown == 0) && ((event.motion.x <= 52 || event.motion.x >= 52 + 32) && (event.motion.y <= 54 || event.motion.y >= 54 + 32)) && (input->data.e == 1))
      {
        if(input->data.numItemInvX != -1 && input->data.numItemInvY != -1)
        {
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
}
