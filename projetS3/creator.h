#pragma once
#include <SDL.h>
#include "fonction.h"

#define PM_START 0
#define POSX_START 352
#define POSY_START 400
#define NBIMAGES	20

//creator.c
void creer_joueur(character *joueur);
void creer_monde(monde *monde);
void creer_input(input *input);
void creer_monstre(monstre *monstre, atlas* atlasJeu, monde monde);
image* creer_texture(char* chemin, int x, int y, int animX, int animY, int animH, int animW);
SDL_Surface* creer_minimap(monde *monde, character *a);
atlas* init_atlas();
int getPosX(image* image);
int getPosY(image* image);
void setPosX(image* image, int x);
void setPosY(image* image, int y);
void setAnimX(image* image, int x);
void setAnimY(image* image, int y);
void setAnimH(image* image, int h);
void setAnimW(image* image, int w);

//generator.c
void gen_monde(monde *monde, int freq);
void gen_cercle(int x, int y, int rayon, monde *monde);
void gen_grottes(monde *monde, int freq);
void apparition_joueur(character *joueur, monde monde);
