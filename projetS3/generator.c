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
  calque *ran = init_calque(TMONDE, 1.);
  calque *grotte = init_calque(TMONDE, 1.);
  for(i=0; i<NB_GROTTES; i++){
    taille_grotte = aleatoire(1, TMONDE/2);
    debut_grotte = aleatoire(0, TMONDE - taille_grotte);

    for(k = debut_grotte; k < (debut_grotte + taille_grotte); k++){
       ran->v[k] = aleatoire(fin->v[k], TMONDE); 
    }

    for(k = debut_grotte; k < (debut_grotte + taille_grotte); k++){
      a = valeur_interpolee(k, freq, ran);
      if(a < fin->v[k]){
        grotte->v[k] = 0;
      }else{
        grotte->v[k] = a/grotte->persistance;
      }
    }

    for(k = debut_grotte; k < (debut_grotte + taille_grotte); k++){
       // Applique le calque dans le monde
      if(grotte->v[k] != 0){
	//Créer un cercle pour faire une grotte
	if(k == (debut_grotte + taille_grotte) - 2){
	  gen_cercle(k, grotte->v[k], (int)round(sqrt(1 + pow(abs(grotte->v[k] - grotte->v[k+1]), 2))+1), monde);
	}else{
         gen_cercle(k, (int)round(sqrt(1 + pow(abs(grotte->v[k-1] - grotte->v[k]), 2))+1), 2, monde);
	}
      }
    }
  }
  free_calque(ran);
  free_calque(grotte);

  free_calque(random);
  free_calque(fin);

  tab_int2char(monde->grilleInt, monde->grilleChar, TMONDE, TMONDE);
  ecrire_fichier("saves/MondeTest.txt", monde->grilleChar, TMONDE, TMONDE);
}


void gen_cercle(int x, int y, int rayon, monde *monde){
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