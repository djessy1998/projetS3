#include <SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include "constant.h"

//init_SDL.c
SDL_Surface* initialisation_SDL();
void initialisation_Jeu(monde *monde, character *joueur, input *input, monstre tabMon[NBMONSTRE], int freq, atlas *atlasJeu, char* arg1);
void compteur_fps();
