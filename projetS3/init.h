#include <SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"

//init_SDL.c
SDL_Surface* initialisation_SDL();
void initialisation_Jeu(monde *monde, character *joueur, input *input, monstre tabMon[NBMONSTRE], int freq, atlas *atlasJeu);
void compteur_fps();
