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
void creer_monstre(monstre *monstre, monde monde);
image* creer_texture(char* chemin, int x, int y, int animX, int animY, int animH, int animW);
SDL_Surface* creer_minimap(monde *monde);
atlas* init_atlas();
void setPosX(image* image, int x);
void setPosY(image* image, int y);
void setAnimY(image* image, int y);

//generator.c
void gen_monde(monde *monde, int freq);
void gen_cercle(int x, int y, int rayon, monde *monde);
void gen_grottes(monde *monde, int freq);
void apparition_joueur(character *joueur, monde monde);
