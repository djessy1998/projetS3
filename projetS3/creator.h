#include <SDL.h>

#define PM_START 0
#define POSX_START 352
#define POSY_START 400


//creator.c
void creer_joueur(character *joueur);
void creer_monde(monde *monde);
void creer_input(input *input);
void creer_monstre(monstre *monstre);
SDL_Surface* creer_texture(char* chemin);

//generator.c
void gen_monde(monde *monde, int freq);
void gen_cercle(int x, int y, int rayon, monde *monde);
void gen_grottes(monde *monde, int freq);