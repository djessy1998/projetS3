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
  
  for(i=0; i<NB_GROTTES; i++){
    taille_grotte = aleatoire(TMONDE/3, TMONDE);
    debut_grotte = aleatoire(0, TMONDE);
    
    for(k = 0; k < taille_grotte; k++){
      random->v[k] = aleatoire(0, TMONDE);
    }
    
    for(k = 0; k < taille_grotte; k++){
      a = valeur_interpolee(k /*+ debut_grotte*/, freq, random);
      if(aleatoire(1, 12) == 1){
	grotte->v[k] = - a/grotte->persistance;
      }else{
	grotte->v[k] = a/grotte->persistance;
      }
    }
    
    int x = 0, y = 0, rayon = 0, limiteX = 0, DroiteGauche = 0;
    for(k = 0; k < taille_grotte; k+= 2){
      //Créer un cercle pour faire une grotte
      rayon = (int)round(sqrt(2 + pow(abs(abs(grotte->v[k]) - abs(grotte->v[k+1])), 2))) +1; // AB² = AC² + BC², AB est le rayon du cercle

      if(grotte->v[k] < 0){
	limiteX = k - limiteX;
	DroiteGauche = !DroiteGauche;
      }
      
      if(DroiteGauche){
	x = debut_grotte + 2*limiteX - k;
      }else{
	x = debut_grotte + k - 2*limiteX;
      }
      
      if(x > TMONDE -1){ //Si hors limite
	x = (TMONDE-1) - (debut_grotte + k)%(TMONDE-1);
      }
      
      if(grotte->v[k] > TMONDE-1){ //Si hors limite
	y = (TMONDE-1) - abs(grotte->v[k])%(TMONDE-1);
      }else{
	y = abs(grotte->v[k]);
      }
      
      gen_cercle(x, y, rayon, monde);
    }
  }

  //Placement des items
  int iRandom = (1 + rand()%(TMONDE - 1));
  int jRandom = (1 +rand()%(TMONDE - 1));

  for(i=0;i<NBITEMS;i++){
    iRandom = (1 + rand()%(TMONDE - 1));
    jRandom = (1 +rand()%(TMONDE - 1));
    int typeItRand = (2 + (rand()%(2)));
    while((monde->grilleInt[iRandom - 1][jRandom] != 0 || monde->grilleInt[iRandom][jRandom] != 1) && (iRandom < TMONDE - 1 && iRandom > 0)){
      if(monde->grilleInt[iRandom - 1][jRandom] == 1 && monde->grilleInt[iRandom + 1][jRandom] == 1){
        iRandom -= 1;
      }
      else{
        iRandom += 1;
      }
    }

    while(monde->grilleInt[iRandom][jRandom+1] == TERRE){
      while(monde->grilleInt[iRandom][jRandom + 1] == TERRE){
        if(iRandom < TMONDE - 1){
          iRandom -= 1;
        }
      }
    }
     monde->grilleInt[iRandom][jRandom] = typeItRand;
  }

  //placement des arbres
  for(i=0;i<NBARBRES;i++){
    int taille = (rand()%8)+3;
    iRandom = (1 + rand()%(TMONDE - 1));
    jRandom = (1 +rand()%(TMONDE - 1));
    while((monde->grilleInt[iRandom-1][jRandom] != 0 || monde->grilleInt[iRandom][jRandom] != 1)){
      if(monde->grilleInt[iRandom - 1][jRandom] == 1 && monde->grilleInt[iRandom + 1][jRandom] == 1 && monde->grilleInt[iRandom][jRandom] == 1 ){
        iRandom -= 1;
      }
      else if(monde->grilleInt[iRandom - 1][jRandom] != 1 && monde->grilleInt[iRandom + 1][jRandom] == 1 && monde->grilleInt[iRandom][jRandom] == 1){
        jRandom = (1 +rand()%(TMONDE - 1));       
      }
      else if(monde->grilleInt[iRandom - 1][jRandom] == 0 && monde->grilleInt[iRandom + 1][jRandom] != 0 && monde->grilleInt[iRandom][jRandom] == 0){
        jRandom = (1 +rand()%(TMONDE - 1));       
      }
      else{
        iRandom += 1;
      }
    }

     for(i=0;i<taille;i++){
      monde->grilleInt[iRandom-1][jRandom-1] = ABG;
      monde->grilleInt[iRandom][jRandom-1] = TERRE;
      monde->grilleInt[iRandom-1][jRandom+1] = ABD;
      monde->grilleInt[iRandom][jRandom+1] = TERRE;
      monde->grilleInt[iRandom-1][jRandom] = BASARB;
      monde->grilleInt[iRandom - taille + (1 - (i - 1))][jRandom] = ARBRE;
      if(i == taille - 1){
          monde->grilleInt[iRandom - taille - 4][jRandom - 2] = TOPARB;
      }
     }
  }        

  //Base en Terre
  for(i=TMONDE -2 ; i<TMONDE; i++){
    for(j=0 ; j<TMONDE; j++){
      monde->grilleInt[i][j] = TERRE;
    }
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
  
  monde->grilleInt[y][x] = 0;
  
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
      if(sqrt(pow(x - i, 2) + pow(y - j, 2)) < sqrt(2*pow(rayon ,2))){
	monde->grilleInt[j][i] = 0;
      }
    }
  }
}
