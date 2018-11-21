#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "fonction.h"
#include "perlin.h"
#include "creator.h"

void gen_monde(monde *monde, int freq){
  //Génération aléatoire de Terrain:
  calque *random = init_calque(TMONDE, 1.);
  calque *fin = init_calque(TMONDE, 1.);
  int i, j, a, k;

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
  
  //Base en Terre
  for(i=TMONDE -2 ; i<TMONDE; i++){
    for(j=0 ; j<TMONDE; j++){
      monde->grilleInt[i][j] = TERRE;
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

  //Génération aléatoire de grottes
  int taille_grotte = 0;
  int debut_grotte = 0;
  calque *grotte = init_calque(TMONDE, 1.);
  int taillefinale = 0;
  
  for(i=0; i<NB_GROTTES; i++){
    taille_grotte = aleatoire(3, TMONDE/2);
    debut_grotte = aleatoire(1, TMONDE - taille_grotte);
    taillefinale = -1; //Car la taille est tout le temps compté avec 1 de trop
    
    for(k = debut_grotte; k < (debut_grotte + taille_grotte); k++){
      random->v[k] = aleatoire(fin->v[k], TMONDE);
    }
    
    for(k = debut_grotte; k < (debut_grotte + taille_grotte); k++){
      a = valeur_interpolee(k, freq, random);
      if(a >= fin->v[k]){
	taillefinale ++;
	grotte->v[taillefinale] = a/grotte->persistance;
      }
    }
    
    for(k = 0; k < taillefinale - 1; k++){
      //Créer un cercle pour faire une grotte
      gen_cercle(k + debut_grotte, grotte->v[k], (int)round(sqrt(1 + pow(abs(grotte->v[k] - grotte->v[k+1]), 2))), monde);
    }
    if(taillefinale >= 0){
      gen_cercle(debut_grotte + taillefinale -1, grotte->v[taillefinale - 1], (int)round(sqrt(1 + pow(abs(grotte->v[taillefinale - 1] - grotte->v[taillefinale - 2]), 2))+1), monde);
    }
  }

  //Placement des items
  int iRandom = (1 + rand()%(TMONDE - 1));
  int jRandom = (1 +rand()%(TMONDE - 1));
  for(i=0;i<NBITEMS;i++){
    int posTrouve = 0;
    iRandom = (1 + rand()%(TMONDE - 1));
    jRandom = (1 +rand()%(TMONDE - 1));
    int typeItRand = (2 + (rand()%(2)));
    while(monde->grilleInt[iRandom - 1][jRandom] != 0 || monde->grilleInt[iRandom][jRandom] != 1){
      if(monde->grilleInt[iRandom - 1][jRandom] == 1 && monde->grilleInt[iRandom + 1][jRandom] == 1){
        iRandom -= 1;
      }
      else{
        iRandom += 1;
      }
    }

    while(monde->grilleInt[iRandom][jRandom+1] == TERRE && posTrouve == 0){
      while(monde->grilleInt[iRandom][jRandom + 1] == TERRE && posTrouve == 0){
        if(iRandom < TMONDE - 1){
          iRandom -= 1;
        }
      }
    }
     monde->grilleInt[iRandom][jRandom] = typeItRand;
  }


  free_calque(grotte);
  free_calque(random);
  free_calque(fin);

  tab_int2char(monde->grilleInt, monde->grilleChar, TMONDE, TMONDE);
  ecrire_fichier("saves/MondeTest.txt", monde->grilleChar, TMONDE, TMONDE);
}


void gen_cercle(int x, int y, int rayon, monde *monde){
  if(rayon > 5){
    rayon = 5;
  }
  monde->grilleInt[x][y] = 0;
  int i, j;
  int debutX = x - rayon;
  int debutY = y - rayon;
  int finX = x + rayon;
  int finY = y + rayon;
  if(debutX < 0){
    debutX = 0;
  }
  if(finX > TMONDE){
    finX = TMONDE;
  }
  if(debutY < 0){
    debutY = 0;
  }
  if(finY > TMONDE){
    finY = TMONDE;
  }
  for(i = debutX; i < finX; i++){
    for(j = debutY; j < finY; j++){
      monde->grilleInt[i][j] = 0;
    }
  }
}
