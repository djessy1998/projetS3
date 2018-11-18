#include <SDL.h>

#define PM_START 0
#define POSX_START 352
#define POSY_START 400

void creer_joueur(character *joueur);
void creer_monde(monde *monde);
void gen_monde(monde *monde, int freq);
void creer_input(input *input);
SDL_Surface* creer_texture(char* chemin);
