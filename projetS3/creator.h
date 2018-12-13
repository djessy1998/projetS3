#pragma once
#include <SDL.h>
#include "fonction.h"
#include "atlas.h"

#define PM_START   0
#define POSX_START 352
#define POSY_START 400

#define JOUEUR_IM 	   0
#define TERREINV_IM	     1
#define CASQUE_IM	     2
#define ARMURE_IM	     3
#define TRONC_IM	     4
#define ABG_IM		     5
#define ABD_IM		     6
#define BASARB_IM	     7
#define TOPARB_IM	     8
#define FONDGROTTE_IM  9
#define TERRESH_IM 	   10
#define HERBE_IM       11
#define HERBE1_IM      12
#define TERRE1_IM      13
#define TERRE2_IM      14
#define TERRE3_IM      15
#define TERREHERBE1_IM 16
#define TERREHERBE2_IM 17
#define TERREHERBE3_IM 18
#define FONDTERRE1_IM  19
#define FONDTERRE2_IM  20
#define FONDTERRE3_IM  21

#define VIEENT_IM	     22
#define INVIM_IM	     23
#define ACTUELINV_IM	 24
#define MIVIE_IM	     25
#define NOVIE_IM	     26
#define CRACK_IM	     27
#define JOUEURD_IM	   28
#define MAP_IM 	       29
#define SLIME_IM	     30
#define BG_IM	         31
#define VIEENTM_IM	   32
#define MIVIEM_IM	     33
#define NOVIEM_IM	     34
#define CLOUD_IM       35
#define CLOUD1_IM      36
#define CLOUD2_IM      37
#define CLOUD3_IM      38
#define ARMUREINV_IM   39
#define CASQUEINV_IM   40



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
