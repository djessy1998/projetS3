#pragma once
#include <SDL.h>
#include "fonction.h"
#include "atlas.h"

#define PM_START 0
#define POSX_START 352
#define POSY_START 400

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
#define VIEENTMIM	20
#define MIVIEMIM	21
#define NOVIEMIM	22
#define TERRESHIM 	23
#define CLOUDIM 24
#define CLOUD1IM 25
#define CLOUD2IM 26
#define CLOUD3IM 27


//creator.c
void creer_joueur(character *joueur);
void creer_monde(monde *monde);
void creer_input(input *input);
void creer_monstre(monstre *monstre, atlas* atlasJeu, monde monde);
SDL_Surface* creer_minimap(monde *monde, character *a);
void sauvegarde(monde *monde);

//destructor.c
void detruire_text(image* image);
void detruire_atlas(atlas* atlas);
void detruire_monde(monde *monde);

//generator.c
void gen_monde(monde *monde, int freq);
void gen_cercle(int x, int y, int rayon, monde *monde);
void gen_grottes(monde *monde, int freq);
void apparition_joueur(character *joueur, monde monde);
