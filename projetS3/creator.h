#pragma once
#include <SDL.h>
#include "fonction.h"
#include "atlas.h"
#include "constant.h"

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
void detruire_Jeu(monde *monde, atlas* atlas, character joueur, Liste* listeItems, monstre tabMon[NBMONSTRE], Mix_Music *MusicMenu);

//generator.c
void gen_monde(monde *monde, int freq);
void gen_cercle(int x, int y, int rayon, monde *monde);
void gen_grottes(monde *monde, int freq);
void apparition_joueur(character *joueur, monde monde);
