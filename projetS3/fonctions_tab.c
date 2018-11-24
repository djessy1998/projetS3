#include "fonctions_fichiers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
      switch (tab[x][y]){
      case CASE8:
  tabInt[x][y] = 8;
      break;
      case CASE7:
  tabInt[x][y] = 7;
      break;
      case CASE6:
  tabInt[x][y] = 6;
      break;
      case CASE5:
  tabInt[x][y] = 5;
      break;
      case CASE4:
  tabInt[x][y] = 4;
      break;
      case CASE3:
  tabInt[x][y] = 3;
        break;
      case CASE2:
  tabInt[x][y] = 2;
        break;
      case CASE1:
	tabInt[x][y] = 1;
        break;
      case CASE0:
	tabInt[x][y] = 0;
        break;
      default:
        break;
      }
    }
  }
}

void tab_int2char(int** tabInt, char** tabChar, int tailleX, int tailleY){
  for(int x = 0; x < tailleX; x++){
    for(int y = 0; y < tailleY; y++){
      switch (tabInt[x][y]){
      case 8:
        tabChar[x][y] = '8';
        break;
      case 7:
        tabChar[x][y] = '7';
        break;
      case 6:
        tabChar[x][y] = '6';
        break;
      case 5:
        tabChar[x][y] = '5';
        break;
      case 4:
        tabChar[x][y] = '4';
        break;
      case 3:
        tabChar[x][y] = '3';
        break;
      case 2:
        tabChar[x][y] = '2';
        break;
      case 1:
	      tabChar[x][y] = '1';
        break;
      case 0:
	      tabChar[x][y] = '0';
        break;
      default:
        break;
      }
    }
  }
}
