#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "fonction.h"
#include "creator.h"
#include "perlin.h"
#include "fonctions_fichiers.h"
#include "constant.h"

void creer_joueur(character *joueur){
  joueur->nom = (char*) malloc(5 * sizeof(char));
  strcpy(joueur->nom, "Jean");
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
  joueur->compt = 0;
  joueur->mort = 0;
  joueur->degatM = 5;
  joueur->invinc = 501;
  joueur->murD = 0;
  joueur->murG = 0;
  joueur->minaX = 0;
  joueur->minaY = 0;
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
  for(i=0;i<4;i++){
    for(j=0;j<10;j++){
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
  input->data.clavier = 1;
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

void creer_monstre(monstre *monstre, atlas* atlasJeu, monde monde){
  monstre->nom = (char*) malloc( 6 * sizeof(char));
  strcpy(monstre->nom, "Slime");
  monstre->PV = 20;
  monstre->x = rand()%(TMONDE-1) +1;
  monstre->y = 0;

  //Apparition du monstre dans le monde
  while(!estSolide(monde.grilleInt[monstre->y][monstre->x])){
    monstre->y += 1;
    if(estSolide(monde.grilleInt[monstre->y][monstre->x+1]) && estSolide(monde.grilleInt[monstre->y][monstre->x-1])){
      monstre->x += 1;
      monstre->y = 0;
    }
  }
  if(estSolide(monde.grilleInt[monstre->y][monstre->x+1])){
    monstre->x -= 1;
  }
  setPosX(atlasJeu->tabIm[SLIME_IM], 0);
  setPosY(atlasJeu->tabIm[SLIME_IM], 0);
  setAnimX(atlasJeu->tabIm[SLIME_IM], 0);
  setAnimY(atlasJeu->tabIm[SLIME_IM], 2);
  setAnimH(atlasJeu->tabIm[SLIME_IM], HAUTEUR_MONSTRE);
  setAnimW(atlasJeu->tabIm[SLIME_IM], LARGEUR_MONSTRE);
  monstre->x = TAILLE_BLOCS*monstre->x;
  monstre->y = TMONDE*TAILLE_BLOCS - TAILLE_BLOCS*monstre->y + HAUTEUR_MONSTRE;
  monstre->velocity_y = 0;
  monstre->velocity_x = 0;
  monstre->saut = IMMOBILE;
  monstre->dernierSaut = IMMOBILE;
  monstre->mort = 0;
  monstre->coupPr = 0;
  monstre->pos.x = 0;
  monstre->pos.y = 0;
  monstre->calculSaut = 0;
}



SDL_Surface* creer_minimap(monde *monde, character *a){
  int i,j;
  static int increment = 0;
  SDL_Surface *temp = NULL;
  SDL_Color colors[5];
  static char numPerso = 4;
  colors[0].r=135;
  colors[0].g=206;
  colors[0].b=235;
  colors[1].r=34;
  colors[1].g=139;
  colors[1].b=34;
  colors[2].r=255;
  colors[2].g=255;
  colors[2].b=255;
  colors[3].r=255;
  colors[3].g=0;
  colors[3].b=0;
  colors[4].r=255;
  colors[4].g=255;
  colors[4].b=0;
  temp = SDL_CreateRGBSurface(SDL_SWSURFACE,200,200,8, 0xff, 0xff, 0xff, 0);
  Uint8 *p = temp->pixels;
  int posJY = TMONDE - ((a->yMonde + (NBBLOCS_FENETREY*TAILLE_BLOCS - a->pos.y) - PLAYER_HEIGHT)/16);
  int posJX = (a->xMonde + a->pos.x)/16;
  if(increment > 60){
    if(numPerso == 3){
      numPerso = 4;
    }else{
      numPerso = 3;
    }
    increment = 0;
  }else{
   increment++;
  }
  for(i=0;i<TMONDE;i+=5){
    for(j=0;j<TMONDE;j+=5){
      if((i >= (posJY - 27) && i<posJY) && (j >= posJX && j<posJX+10)){
        *p = numPerso;
        p++;
      }else{
        if(estSolide(monde->grilleInt[i][j])){
          *p = 1;
        }else{
          *p = monde->grilleInt[i][j];
        }
        p++;
      }
    }
  }
  SDL_SetPalette(temp,SDL_LOGPAL|SDL_PHYSPAL, colors, 0, 5);
  SDL_Surface* tex = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  return tex;
}


void sauvegarde(monde *monde){
  tab_int2char(monde->grilleInt, monde->grilleChar, TMONDE, TMONDE);
  ecrire_fichier("saves/MondeTest.txt", monde->grilleChar, TMONDE, TMONDE);
}
