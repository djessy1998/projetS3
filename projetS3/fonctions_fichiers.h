#include <stdlib.h>
#include <stdio.h>
#include "constant.h"

char** allouer_tab_2D_char(int n, int m);
int** allouer_tab_2D_int(int n, int m);
void desallouer_tab_2D_char(char** tab, int n);
void desallouer_tab_2D_int(int** tab, int n);
void afficher_tab_2D_char(char** tab, int n, int m);
void afficher_tab_2D_int(int** tab, int n, int m);
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol);
char** lire_fichier(const char* nomFichier);
char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau);
void ecrire_fichier(const char* nomFichier, char** tab, int n, int m);
void tab_char2int(char** tab, int** tabInt, int tailleX, int tailleY);
void tab_int2char(int** tabInt, char** tabChar, int tailleX, int tailleY);
