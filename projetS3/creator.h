#pragma once
#include <SDL.h>
#include "fonction.h"

#define PM_START 0
#define POSX_START 352
#define POSY_START 400
#define NBIMAGES	20

#define JOUEURIM 	0
#define VIEENTIM	1
#define	CASQUEIM	2
#define	ARMUREIM	3
#define INVIMIM	4
#define ACTUELINVIM	5
#define MIVIEIM	6
#define NOVIEIM	7
#define CRACKIM	8
#define	JOUEURDIM	9
#define TRONCIM	10
#define ABGIM		11
#define ABDIM		12
#define TOPARBIM	13
#define BASARBIM	14
#define MAPIM 	15
#define SLIMEIM	16
#define FONDGROTTEIM 	17
#define TERREIM	18
#define BGIM	19


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
void detruire_text(image* image);

//generator.c
void gen_monde(monde *monde, int freq);
void gen_cercle(int x, int y, int rayon, monde *monde);
void gen_grottes(monde *monde, int freq);
void apparition_joueur(character *joueur, monde monde);
