#include <SDL.h>
#include "fonctions_fichiers.h"

#define SCREEN_WIDTH   720
#define SCREEN_HEIGHT  560
#define PLAYER_WIDTH   20
#define PLAYER_HEIGHT  54
#define FORCE_GRA      0.2
#define VITESSE        0.09
#define VITESSEJ       0.2
#define TMONDE         100
#define NBBLOCS_FENETREX 47
#define NBBLOCS_FENETREY 37
#define NB_BLOCS_AU_DESSUS_JOUEUR 25
#define TAILLE_BLOCS	 16

#define VIDE  0
#define TERRE 1

typedef struct character character;
struct character
{
  char name[30];
  int PV;
  int PM;
  int xMonde;
  int yMonde;
  SDL_Rect pos;
  int type;
  int boolItem;

};

typedef struct items items;
struct items
{
	int xMondeItem;
	int yMondeItem;
	int type;
  double avG;
  double avD;
	items *suivant;
};

typedef struct Liste Liste;
struct Liste
{
    items *premier;
};

void deplacerG(character *a, float *vitesse, int murGau, int murDro, float *vitesseMur);
void deplacerD(character *a, float *vitesse, int murDro, int murGau, float *vitesseMur);
void gravite(character *a, float *force);
void collision(character *a, int affichage[NBBLOCS_FENETREY][NBBLOCS_FENETREX], float *force,int *bloquerG, int *bloquerD, int posB[TMONDE][TMONDE], int posBY[TMONDE][TMONDE], int *saut);
void sauter(character *a, int *saut, float *x, float *y, int murDro, int murGau);
void baisser(character *a);
void terreRonde(int *xMondeBl, character *a, int *murDro, int *murGau);
void afficherListe(Liste *liste);
void suppression(Liste *liste);
void insertion(Liste *liste, int nvType, int nvXMonde, int nvYMonde);
Liste *initialisation();
void cliquerItemInv(items inv[4][10]);
void TrierInv(int rienI, items inv[4][10], int type);
void afficherElementsListe(Liste *liste, int *ItemAffich , int dirChar,character *a, SDL_Surface *screen, SDL_Surface *casque, SDL_Surface *armure);
void collisionItems(Liste *liste, int dirChar, int ItemAffich, int bloquerG, int bloquerD, character *a, int gauche, int droite);
