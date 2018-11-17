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
  joueur->PV = PV_START;
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
  monde->grilleChar = lire_fichier("saves/Monde1.txt");
  monde->grilleInt = allouer_tab_2D_int(TMONDE, TMONDE);
  tab_char2int(monde->grilleChar, monde->grilleInt, TMONDE, TMONDE);
  desallouer_tab_2D_char(monde->grilleChar, TMONDE);


  monde->posB = allouer_tab_2D_int(TMONDE, TMONDE);
  monde->posBY = allouer_tab_2D_int(TMONDE, TMONDE);
  monde->affichage = allouer_tab_2D_int(NBBLOCS_FENETREY, NBBLOCS_FENETREX);
}

void gen_monde(monde *monde, int freq){
  //Génération aléatoire de Terrain:
  calque *random;
  random = init_calque(TMONDE, 1.);
  calque *fin = init_calque(TMONDE, 1.);
  int i, j, a;

  //calque de base aléatoire.
  for(i=0; i<TMONDE; i++){
     random->v[i] = aleatoire((2*NBBLOCS_FENETREY)/3, TMONDE);
  }

  for(j=0; j<TMONDE; j++){
     a = valeur_interpolee(j, freq, random);
     fin->v[j] = a/fin->persistance;
  }

  //Le monde a 0
  for(i=0 ; i<TMONDE; i++){
    for(j=0 ; j<TMONDE; j++){
      monde->grilleInt[i][j] = VIDE;
    }
  }

  for(i=0 ; i<TMONDE; i++){
     // Applique le calque dans le monde
     monde->grilleInt[fin->v[i]][i] = TERRE;
     //Remplissage de bas en haut
     for(j = fin->v[i]; j<TMONDE; j++){
       monde->grilleInt[j][i] = TERRE;
     }
  }
  free_calque(random);
  free_calque(fin);

  tab_int2char(monde->grilleInt, monde->grilleChar, TMONDE, TMONDE);
  ecrire_fichier("saves/MondeTest.txt", monde->grilleChar, TMONDE, TMONDE);
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
      input->data.inv[i][j].nomItem = "Rien";
      if(input->data.inv[i][j].type == 1){
        input->data.inv[i][j].nomItem = "Casque";
      }
      if(input->data.inv[i][j].type == 2){
        input->data.inv[i][j].nomItem = "Armure";
      }
    }
  }
}


SDL_Surface* creer_texture(char* chemin){
  SDL_Surface *temp = NULL;
  temp = SDL_LoadBMP(chemin);
  SDL_Surface* tex = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  return tex;
}
