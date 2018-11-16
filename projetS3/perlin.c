#include "perlin.h"

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

calque* init_calque(int t, float p){
  calque *s = malloc(sizeof(calque));
  s->v = malloc(t*sizeof(int*));
  int i;
  for(i=0; i<t; i++){
    s->v[i] = 0;
  }
  s->taille = t;
  s->persistance = p;
  
  return s;
}

void free_calque(calque* s){
  free(s->v);
  free(s);
}

unsigned char aleatoire(float a){
  return (float)rand() / RAND_MAX * a;
}

int valeur_interpolee(int i, int freq, calque *r){
  int borne1, borne2, q;
  float pas;
  pas = (float)r->taille/freq;
  
  q = (float)i/pas;
  borne1 = q*pas;
  borne2 = (q+1)*pas;
  
  if(borne2 >= r->taille){
    borne2 = r->taille - 1;
  }
  
  int b0, b1;
  b0 = r->v[borne1];
  b1 = r->v[borne2];
  
  int fin = interpolate(b0, b1, borne2-borne1, i-borne1);
  return fin;
}

int interpolate(int y1, int y2, int n, int delta){
  if(n==0){
    return y1;
  }
  if(n==1){
    return y2;
  }
  
  float a = (float)delta/n;
  
   float v1 = 3*pow(1-a, 2) - 2*pow(1-a, 3);
   float v2 = 3*pow(a, 2) - 2*pow(a, 3);
   
   return y1*v1 + y2*v2;
}
