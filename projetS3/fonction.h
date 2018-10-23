#include <SDL.h>
#include "fonctions_fichiers.h"

#define SCREEN_WIDTH   720
#define SCREEN_HEIGHT  560
#define PLAYER_WIDTH   20
#define PLAYER_HEIGHT  54
#define FORCE_GRA      0.2
#define VITESSE        0.15
#define VITESSEJ       0.2
#define TMONDE         100
#define NBBLOCS_FENETREX 47
#define NBBLOCS_FENETREY 37
#define NB_BLOCS_AU_DESSUS_JOUEUR 25
#define TAILLE_BLOCS	 16

#define VIDE  0
#define TERRE 1

typedef struct monde monde;
struct monde
{
  char** grilleChar;
  int** grilleInt;
  int** affichage;
  int xMondeB;
  int yMondeB;
  int** posB;
  int** posBY;
};

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
  double x_saut;
  double y_saut;
  double yMondeDouble;
  double xMondeDouble;
  double xPosBloquageDouble;
  
};

typedef struct items items;
struct items
{
  int xMondeItem;
  int yMondeItem;
  int type;
  int boolean;
  double increment;
  double avG;
  double avD;
  SDL_Rect SortIm;
  SDL_Rect SortImPos;
  SDL_Rect posItemMonde;
  items *suivant;
};

typedef struct Liste Liste;
struct Liste
{
    items *premier;
};



typedef struct InputData InputData;
struct InputData
{
  int quit;
  int z;
  int q;
  int s;
  int d;
  int e;
  int f;
  int butDown;
  int numItemInvX;
  int numItemInvY;
  SDL_Rect posImage;
  int i;
  int j;
  int n;
  items inv[4][10];
  int supprimer;
  int getB;
  int rien;
  int typeMemoire;
};



typedef struct input input;
struct input
{
  InputData data;
};


void fonction_Handle_Event(SDL_Event event, input *input);

void deplacerG(character *a, int murGau, int murDro);
void deplacerD(character *a, int murDro, int murGau);
void gravite(character *a);
void collision(character *a, int** affichage, int *bloquerG, int *bloquerD, int** posB, int** posBY, int *saut, int *murDr);
void sauter(character *a, int *saut, int murDro, int murGau);
void baisser(character *a);
void terreRonde(character *a, int *murDro, int *murGau, int *murHau);
void afficherListe(Liste *liste);
void suppression(Liste *liste);
void insertion(Liste *liste, int nvType, int nvXMonde, int nvYMonde);
Liste *initialisation();
void cliquerItemInv(items inv[4][10]);
void TrierInv(int rienI, items inv[4][10], int type);
void afficherElementsListe(Liste *liste, int *ItemAffich, int dirChar, character *a, SDL_Surface *screen, SDL_Surface *casque, SDL_Surface *armure, int q, int d, int bloqD, int bloqG);
void collisionItems(Liste *liste, int dirChar, int ItemAffich, int bloquerG, int bloquerD, character *a, int gauche, int droite, int murG, int murD);
