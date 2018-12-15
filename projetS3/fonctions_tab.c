#include "fonctions_fichiers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fonction.h"
#include "constant.h"
char** allouer_tab_2D_char(int n, int m){
  char** tab2D;
  tab2D = (char**) malloc(n * sizeof(char*));

  tab2D[0] = (char *)malloc(n*m*sizeof(char));

  for(int i=1; i<n ; i++){
    tab2D[i] = tab2D[i-1] + m;
  }
  for(int i = 0; i < n; i++){
    for(int y = 0; y < m; y++){
      tab2D[i][y] = ' ';
    }
  }
  return tab2D;
}

int** allouer_tab_2D_int(int n, int m){
  int** tab2D;
  tab2D = (int**) malloc(n * sizeof(int*));

  tab2D[0] = (int *)malloc(n*m*sizeof(int));

  for(int i=1; i<n ; i++){
    tab2D[i] = tab2D[i - 1] + m;
  }
  for(int i = 0; i < n; i++){
    for(int y = 0; y < m; y++){
      tab2D[i][y] = 0;
    }
  }
  return tab2D;
}

void desallouer_tab_2D_char(char** tab, int n){
  free(*tab);
  free(tab);
}

void desallouer_tab_2D_int(int** tab, int n){
  free(*tab);
  free(tab);
}

void afficher_tab_2D_char(char** tab, int n, int m){
  printf("Affichage tableau à 2 dimensions de %dx%d :\n", n, m);
  for(int i = 0; i < n; i++){
    for(int y = 0; y < m; y++){
      printf("%c", tab[i][y]);
    }
  }
}

void afficher_tab_2D_int(int** tab, int n, int m){
  printf("Affichage tableau à 2 dimensions de %dx%d :\n", n, m);
  for(int i = 0; i < n; i++){
    for(int y = 0; y < m; y++){
      printf("%d", tab[i][y]);
    }
    printf("\n");
  }
}

void tab_char2int(char** tab, int** tabInt, int tailleX, int tailleY){
  for(int x = 0; x < tailleX; x++){
    for(int y = 0; y < tailleY; y++){
      tabInt[x][y] = (int)(tab[x][y]) - VALEUR_ASCII_0;
    }
  }
}

void tab_int2char(int** tabInt, char** tabChar, int tailleX, int tailleY){
  for(int x = 0; x < tailleX; x++){
    for(int y = 0; y < tailleY; y++){
      tabChar[x][y] = tabInt[x][y] + VALEUR_ASCII_0;
    }
  }
}
