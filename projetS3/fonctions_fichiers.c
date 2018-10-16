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



void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol){
  FILE* ptrFichier = fopen(nomFichier,"r");
  int maxCol = 0;
  int Col = 0;
  int totalLigne = 0;
  int c;
  if(ptrFichier == NULL){
    perror("Erreur ouverture Fichier");
  }
  do{
    c = fgetc(ptrFichier);
    if(c == '\n'){
      if(maxCol < Col){
	       maxCol = Col;
      }
      totalLigne++;
      Col = 0;
    }
    Col++;
  } while(c != EOF);

  *nbLig = totalLigne;
  *nbCol = maxCol;
  fclose(ptrFichier);
}


char** lire_fichier(const char* nomFichier){
  FILE* ptrFichier = fopen(nomFichier,"r");
  if(ptrFichier == NULL){
    perror("Erreur ouverture Fichier");
  }
  int c;
  int nbLig = 0, nbCol = 0;
  taille_fichier(nomFichier, &nbLig, &nbCol);
  char** tab = allouer_tab_2D_char(nbLig, nbCol);
  for(int i = 0; i<nbLig; i++){
    for(int y = 0; y<nbCol; y++){
      c = fgetc(ptrFichier);
      if(c == EOF){
	       break;
      }
      tab[i][y] = c;
    }
  }
  fclose(ptrFichier);
  return tab;
}


char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau){
  for(int i = 0; i<n; i++){
    for(int y = 0; y<m; y++){
      if(tab[i][y] == ancien){
	       tab[i][y] = nouveau;
      }
    }
  }
  return tab;
}


void ecrire_fichier(const char* nomFichier, char** tab, int n, int m){
  FILE* ptrFichier = fopen(nomFichier,"r");
  if(ptrFichier == NULL){
    perror("Erreur ouverture Fichier");
  }

  for(int i = 0; i<n; i++){
    for(int y = 0; y<m; y++){
      fputc(tab[i][y], ptrFichier);
    }
  }
  fclose(ptrFichier);
}

void tab_char2int(char** tab, int** tabInt, int tailleX, int tailleY){
  for(int x = 0; x < tailleX; x++){
    for(int y = 0; y < tailleY; y++){
      switch (tab[x][y]){
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
