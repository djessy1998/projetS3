#include "fonctions_fichiers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
  FILE* ptrFichier = fopen(nomFichier,"w");
  if(ptrFichier == NULL){
    perror("Erreur ouverture Fichier");
  }

  for(int i = 0; i<n; i++){
    for(int y = 0; y<m; y++){
      fputc(tab[i][y], ptrFichier);
    }
    fputc('\n', ptrFichier);
  }
  fclose(ptrFichier);
}
