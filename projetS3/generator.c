#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "fonction.h"
#include "perlin.h"
#include "creator.h"
#include "constant.h"

void gen_monde(monde *monde, int freq){
  //Génération aléatoire de Terrain:
  calque *random = init_calque(TMONDE, 1.);
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

  free_calque(random);

  //Le monde a 0
  for(i=0 ; i<TMONDE; i++){
    for(j=0 ; j<TMONDE; j++){
      monde->grilleInt[i][j] = VIDE;
    }
  }

  for(i=0 ; i<TMONDE; i++){
     //Remplissage de bas en haut en fonction du calque
     for(j = fin->v[i]; j<TMONDE; j++){
       monde->grilleInt[j][i] = rand()%(TERRE3 - TERRE1 + 1) + TERRE1;
     }
  }

  //On ajoute l'herbe ensuivant le calque
  for(j = 0; j<TMONDE; j++){
    monde->grilleInt[fin->v[j]][j] = rand()%(TERREHERBE3 - TERREHERBE1 + 1) + TERREHERBE1;
  }

   //Génération aléatoire de grottes
   for(i=0; i<NB_GROTTES; i++){
     gen_grottes(monde, freq);
   }

  //Base en Terre
  for(i=TMONDE -2 ; i<TMONDE; i++){
    for(j=0 ; j<TMONDE; j++){
      monde->grilleInt[i][j] = rand()%(TERRE3 - TERRE1 + 1) + TERRE1;
    }
  }

  //Ici on supprime la création des grottes qui sont dqns le ciel
  for(i=0 ; i<TMONDE; i++){
     //Remplissage de bas en haut
     for(j = 0; j<fin->v[i]; j++){
       if(estVide(monde->grilleInt[j][i])){
	        monde->grilleInt[j][i] = VIDE;
       }
     }
  }

  //Placement des items
  int iRandom = (1 + rand()%(TMONDE - 1));
  int jRandom = (1 +rand()%(TMONDE - 1));

  for(i=0;i<NBITEMS;i++){
    iRandom = (1 + rand()%(TMONDE - 2));
    jRandom = (1 +rand()%(TMONDE - 2));
    int typeItRand = (2 + (rand()%(2)));
    while(!estVide(monde->grilleInt[iRandom - 1][jRandom]) || !estSolide(monde->grilleInt[iRandom][jRandom])){
      if(estSolide(monde->grilleInt[iRandom - 1][jRandom]) &&
         estSolide(monde->grilleInt[iRandom + 1][jRandom]) &&
         estSolide(monde->grilleInt[iRandom][jRandom])){
        iRandom -= 1;
      }else{
        iRandom += 1;
      }
    }

    while(estSolide(monde->grilleInt[iRandom][jRandom+1])){
      while(estSolide(monde->grilleInt[iRandom][jRandom + 1])){
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
    iRandom = (1 + rand()%(TMONDE - 2));
    jRandom = (1 +rand()%(TMONDE - 2));
    while((!estSolide(monde->grilleInt[iRandom + 1][jRandom]) || monde->grilleInt[iRandom][jRandom] != VIDE) && (iRandom > 2 && iRandom < TMONDE - 2)){
      if(estSolide(monde->grilleInt[iRandom - 1][jRandom]) &&
         estSolide(monde->grilleInt[iRandom + 1][jRandom]) &&
         estSolide(monde->grilleInt[iRandom][jRandom])){
        iRandom -= 1;
      }else if(monde->grilleInt[iRandom - 1][jRandom] > TERRE && !estSolide(monde->grilleInt[iRandom - 1][jRandom]) &&
              estSolide(monde->grilleInt[iRandom + 1][jRandom]) &&
              estSolide(monde->grilleInt[iRandom][jRandom])){
        jRandom = (1 +rand()%(TMONDE - 1));
      }
      if(monde->grilleInt[iRandom - 1][jRandom] == VIDE && monde->grilleInt[iRandom + 1][jRandom] == VIDE && monde->grilleInt[iRandom][jRandom] == VIDE){
	       iRandom += 1;
      }
      else if(monde->grilleInt[iRandom - 1][jRandom] == VIDE && (monde->grilleInt[iRandom + 1][jRandom] > TERRE && !estSolide(monde->grilleInt[iRandom + 1][jRandom])) && monde->grilleInt[iRandom][jRandom] == VIDE){
	       jRandom = (1 +rand()%(TMONDE - 1));
      }
      else{
	       iRandom -= 1;
      }
    }

    for(j=1;j<=taille;j++){
      monde->grilleInt[iRandom][jRandom] = BASARB;
      if(!estSolide(monde->grilleInt[iRandom][jRandom-1]) && monde->grilleInt[iRandom][jRandom-1] != FONDGROTTE && estSolide(monde->grilleInt[iRandom+1][jRandom-1])){
        monde->grilleInt[iRandom][jRandom-1] = ABG;
      }
      if(!estSolide(monde->grilleInt[iRandom][jRandom+1]) && monde->grilleInt[iRandom][jRandom+1] != FONDGROTTE && estSolide(monde->grilleInt[iRandom+1][jRandom+1])){
        monde->grilleInt[iRandom][jRandom+1] = ABD;
      }
      if(iRandom - j > 0){
	     monde->grilleInt[iRandom-j][jRandom] = ARBRE;
      }
      if(j == taille - 1){
	  if(iRandom - taille - 4 > 0){
	    monde->grilleInt[iRandom - taille - 1][jRandom] = TOPARB;
	  }
      }
     }
  }

  for(i=0 ; i<TMONDE; i++){
     // Applique le calque dans le monde
     if(monde->grilleInt[fin->v[i] - 1][i] == VIDE && !estVide(monde->grilleInt[fin->v[i]][i])){
        monde->grilleInt[fin->v[i] - 1][i] = rand()%(HERBE1-HERBE + 1) + HERBE;
     }
  }


  free_calque(fin);

  tab_int2char(monde->grilleInt, monde->grilleChar, TMONDE, TMONDE);
  ecrire_fichier("saves/MondeTest.txt", monde->grilleChar, TMONDE, TMONDE);
}

void gen_grottes(monde *monde, int freq){
  //Génération aléatoire de grottes
  int taille_grotte = aleatoire(TMONDE/3, TMONDE);
  int debut_grotte = aleatoire(0, TMONDE);
  calque *grotte = init_calque(TMONDE, 1.);
  calque *random = init_calque(TMONDE, 1.);

  int k, a;
  int x = 0, y = 0, rayon = 0, limiteX = 0, direction_grotte = 0;

  //calque aléatoire
  for(k = 0; k < taille_grotte; k++){
    random->v[k] = aleatoire(0, TMONDE);
  }

  //On détermine les valeurs pour faire une "courbe"
  for(k = 0; k < taille_grotte; k++){
    a = valeur_interpolee(k, freq, random);
    //On a 1 chance sur 10 pour que la grotte change de direction
    if(aleatoire(1, 10) == 1){
      grotte->v[k] = (int)-a/grotte->persistance;
    }else{
      grotte->v[k] = (int)a/grotte->persistance;
    }
  }

  //On génère la grotte avec des cercles
  for(k = 0; k < taille_grotte; k += 2){

    rayon = (int)round(sqrt(2 + pow(abs(abs(grotte->v[k]) - abs(grotte->v[k+1])), DIST_ENTRE_POINTS))) +1; // AB² = AC² + BC², AB est le rayon du cercle

    if(grotte->v[k] < 0){
      limiteX = k - limiteX; //On reprend l'ancienne limite pour repartir du même point, mais dans une direction différente
      direction_grotte = !direction_grotte; //Changement de direction
    }

    if(direction_grotte){
      x = debut_grotte + 2*limiteX - k; //Vers la gauche
    }else{
      x = debut_grotte + k - 2*limiteX; //Vers la droite
    }

    if(x > TMONDE -1){ //Si hors limite en X
      x = (TMONDE-1) - (debut_grotte + k)%(TMONDE-1); // On change la direction
    }

    if(grotte->v[k] > TMONDE-1){ //Si hors limite en Y
      y = (TMONDE-1) - abs(grotte->v[k])%(TMONDE-1); // On change la direcion
    }else{
      y = abs(grotte->v[k]);
    }

    gen_cercle(x, y, rayon, monde);
  }
  free_calque(grotte);
  free_calque(random);
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

  //Génération du cercle
  for(i = debutX; i < finX; i++){
    for(j = debutY; j < finY; j++){
      if(sqrt(pow(x - i, 2) + pow(y - j, 2)) < sqrt(2*pow(rayon ,2))){
	       monde->grilleInt[j][i] = rand()%(FONDTERRE3 - FONDTERRE1 + 1) + FONDTERRE1;
      }
    }
  }
}

void apparition_joueur(character *joueur, monde monde){
  int y = NBBLOCS_FENETREY;
  int x = TMONDE/2;

  while(!estSolide(monde.grilleInt[y][x])){
    y += 1;
    if(estSolide(monde.grilleInt[y][x+1]) && estSolide(monde.grilleInt[y][x-1])){
      x += 1;
      y = NBBLOCS_FENETREY;
    }
  }
  joueur->yMonde = (TMONDE - (y+(NBBLOCS_FENETREY - NB_BLOCS_AU_DESSUS_JOUEUR)))*TAILLE_BLOCS + 1;
  joueur->yMondeDouble = (double)joueur->yMonde;
  joueur->xMonde = (x - NBBLOCS_FENETREX/2)*TAILLE_BLOCS;
  joueur->xMondeDouble = (double)joueur->xMonde;
}
