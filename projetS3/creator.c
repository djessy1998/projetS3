#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "fonction.h"
#include "creator.h"
#include "perlin.h"
#include "fonctions_fichiers.h"

void creer_joueur(character *joueur){
  joueur->nom = (char*) malloc(4 *sizeof(char));
  joueur->nom[0] = 'J';
  joueur->nom[1] = 'e';
  joueur->nom[2] = 'a';
  joueur->nom[3] = 'n';
  joueur->PV = FULL_VIE;
  joueur->PM = PM_START;
  joueur->pos.x = POSX_START;
  joueur->pos.y = POSY_START - PLAYER_HEIGHT;
  joueur->xMonde = (TMONDE*TAILLE_BLOCS)/2+7;
  joueur->yMonde = 100;
  joueur->velocity_y = VELOCITE_MAX;
  joueur->yMondeDouble = (double)joueur->yMonde;
  joueur->xMondeDouble = (double)joueur->xMonde;
  joueur->xPosBloquageDouble = (double)joueur->pos.x;
  joueur->yPosBloquageDouble = (double)joueur->pos.y;
  joueur->dir = 1;
  joueur->bloqAGauche = 0;
  joueur->bloqADroite = 0;
  joueur->autorisationSaut = 1;
}


void creer_monde(monde *monde){
  if(TMONDE == 100){
    monde->grilleChar = lire_fichier("saves/Monde1.txt");
  }else if(TMONDE == 1000){
    monde->grilleChar = lire_fichier("saves/Monde2.txt");
  }
  monde->grilleInt = allouer_tab_2D_int(TMONDE, TMONDE);
  tab_char2int(monde->grilleChar, monde->grilleInt, TMONDE, TMONDE);

  monde->posB = allouer_tab_2D_int(TMONDE, TMONDE);
  monde->posBY = allouer_tab_2D_int(TMONDE, TMONDE);
  monde->affichage = allouer_tab_2D_int(NBBLOCS_FENETREY, NBBLOCS_FENETREX);
}



void creer_input(input *input){
  int i;
  int j;
  //Remplis l'inventaire d'éléments vide
  for(i=0;i<4;i++)
    {
      for(j=0;j<10;j++)
	{
	  input->data.inv[i][j].type = -1;
	}
    }

  input->data.inv[0][0].type = 1;
  input->data.inv[0][1].type = 2;
  input->data.quit = 0;
  input->data.z = 0;
  input->data.q = 0;
  input->data.s = 0;
  input->data.d = 0;
  input->data.e = 0;
  input->data.f = 0;
  input->data.Un = 1;
  input->data.butDown = 0;
  input->data.numItemInvX = -1;
  input->data.numItemInvY = -1;
  input->data.n = 0;
  input->data.supprimer = 0;
  input->data.getB= 0;
  input->data.rien = 0;
  input->data.typeMemoire = 0;

  for(i=0;i<4;i++){
    for(j=0;j<10;j++){
      input->data.inv[i][j].nomItem = " ";
      if(input->data.inv[i][j].type == 1){
        input->data.inv[i][j].nomItem = "Casque";
      }
      if(input->data.inv[i][j].type == 2){
        input->data.inv[i][j].nomItem = "Armure";
      }
    }
  }
}

void creer_monstre(monstre *monstre){
  monstre->nom = "Slime";
  monstre->PV = 100;
  monstre->x = TMONDE/2;
  monstre->y = TMONDE/2;
  monstre->pos.x = 50;
  monstre->pos.y = 50;
  monstre->anim.x = 0;
  monstre->anim.y = 2;
  monstre->anim.h = 22;
  monstre->anim.w = 32;
}


SDL_Surface* creer_texture(char* chemin){
  SDL_Surface *temp = NULL;
  temp = SDL_LoadBMP(chemin);
  SDL_Surface* tex = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  return tex;
}
