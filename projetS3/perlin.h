#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constant.h"

typedef struct calque calque;
struct calque{
  int *v;
  int taille;
  float persistance;
};


calque* init_calque(int t, float p);
void free_calque(calque* s);
int aleatoire(int borneMin, int borneMax);
int valeur_interpolee(int i, int freq, calque *r);
int interpolate(int y1, int y2, int n, int delta);
