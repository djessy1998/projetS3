#pragma once
#include <SDL.h>
#include <SDL/SDL_ttf.h>
#include "fonctions_fichiers.h"
#include "atlas.h"

#define SCREEN_WIDTH   720
#define SCREEN_HEIGHT  560

#define PLAYER_WIDTH   22
#define PLAYER_HEIGHT  54

#define VELOCITE_MAX   15
#define VITESSE        1.
#define VITESSEJ       0.2
#define FULL_VIE       100
#define DISTCHUTEMPV   100

#define VELOCITE_MAX_MONSTRE 10
#define HAUTEUR_MONSTRE 22
#define LARGEUR_MONSTRE 32
#define DROITE 1
#define GAUCHE -1
#define IMMOBILE 0

#define TMONDE         1000
#define NB_GROTTES     10
#define DIST_ENTRE_POINTS 2

#define NBBLOCS_FENETREX 47
#define NBBLOCS_FENETREY 37
#define NB_BLOCS_AU_DESSUS_JOUEUR 25

#define RAYONRAM	     40
#define NBITEMS        5
#define NBARBRES       100
#define MAXITINV       64
#define LIMITEMINA      5
#define VITESSEMINA	1

#define TAILLE_BLOCS	 16
#define VIDE  0
#define TERRE 1
#define CASQUE 2
#define ARMURE 3
#define ARBRE 4
#define ABG 5
#define ABD 6
#define BASARB 7
#define TOPARB 8
#define FONDGROTTE 9
#define TERRESH 10

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
  char* nom;
  int PV;
  int PM;
  int degatM;
  int xMonde;
  int yMonde;
  double yMondeDouble;
  double xMondeDouble;
  SDL_Rect pos;
  int type;
  int boolItem;
  double velocity_y;
  int autorisationSaut;
  int sautH;
  double xPosBloquageDouble;
  double yPosBloquageDouble;
  int dir;
  int bloqADroite;
  int bloqAGauche;
  int compt;
  int mort;
};

typedef struct monstre monstre;
struct monstre
{
  char* nom;
  int PV;
  int x;
  int y;
  int velocity_y;
  int velocity_x;
  int saut;
  int dernierSaut;
  int mort;
  int coupPr;
};

typedef struct items items;
struct items
{
  char *nomItem;
  int iItem;
  int jItem;
  int type;
  int trouveInv;
  int numeroItem;
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
  int clavier;
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


//input.c
void fonction_Handle_Event(SDL_Event event, input *input, character *a, monde *monde,int *incAnim, int *minaX, int *minaY, int *choixAct);
void quit(input *input);
void Mouse_Down(SDL_Event event, input *input);
void Mouse_Up(SDL_Event event, input *input);
void Mouse_Motion(SDL_Event event, input *input, character *a, monde *monde,int *incAnim, int *minaX, int *minaY);

//deplacement.c
void deplacerG(character *a, int murGau, int murDro);
void deplacerD(character *a, int murDro, int murGau);
void sauter(character *a);
void baisser(character *a);

//deplacement_monstre.c
void gravite_monstre(monstre *m, monde monde);
int estAuSol_monstre(monstre *m, monde monde);
void sautDroite_monstre(monstre *m);
void sautGauche_monstre(monstre *m);
int bloc_dans_monstre(monstre *m, monde monde);
void pseudo_IA_monstre(monstre *m, character joueur);
void bloc_au_dessus(monstre *m, monde monde);

//collision.c
void gravite(character *a);
void collision(character *a, int** affichage, int** posB, int** posBY, int *murDr, int *murGa, int *yMomTom, int *fait, int *faitCalc, int *yMomTomDeb, int *touche);
void terreRonde(character *a, int *murDro, int *murGau);

//vie.c
void calc_vie_tombe(character *a, int *yMomTomDeb, int *faitCalc, int *touche);

//listes.c
Liste *initialisation();
void cliquerItemInv(items inv[4][10]);
void TrierInv(int rienI, items inv[4][10], int type);
void afficherElementsListe(Liste *liste, int *ItemAffich, character *a, SDL_Surface *screen, SDL_Surface *casque, SDL_Surface *armure, int q, int d, monde *mondeBlocs);
void collisionItems(Liste *liste, int ItemAffich, character *a, int gauche, int droite,int murG, int murD);
void collisionIt(Liste *liste, int **posBY, int **posBX, monde monde, int ItemAffich);
void afficherListe(Liste *liste);
void suppression(Liste *liste);
void insertion(Liste *liste, int nvType, int nvXMonde, int nvYMonde);
void ItemMonde(monde monde, Liste *liste);

//traitement_input.c
void traitement_input(input input, character *joueur1, int murG, int murD, int gauche, int droite, Liste *listeItems, int ItemAffich, atlas* atlasJeu, int *incrim);
void traitement_input_inv(input *input, character *joueur1, Liste *liste, int ItemAffich, monde *monde, atlas* atlasJeu, SDL_Surface *screen);

//affichage.c
void affichage_monde(monde monde, character joueur1, atlas* atlasJeu,SDL_Surface *screen);
void affichage_items_inv(input input, atlas* atlasJeu, SDL_Surface *screen);
void affichage_personnage(character *joueur1, atlas* atlasJeu, SDL_Surface *screen, int invi);
void affichage_vie_personnage(character *a, atlas* atlasJeu, SDL_Surface *screen);
void affichage_barre_inv(input *input,int *choixAct, atlas* atlasJeu, SDL_Surface *screen);
void affichage_crack(monde *monde, int *incAnim, atlas* atlasJeu,int minaX,int minaY, character *a, SDL_Surface *screen);
void affichage_monstre(monstre *monstre, atlas* atlasJeu, SDL_Surface *screen, character joueur);
void affichage_vie_monstre(monstre *monstre, atlas* atlasJeu, SDL_Surface *screen, character *a);
void affichage_nuage(atlas* atlasJeu, SDL_Surface *screen, int *posyR, double *posxR);

//minage.c
void minage(input *input, character *a, int minaY, int minaX, int *incAnim, monde *monde);

//construction.c
void construction(monde *monde, input *input, character *a, int *choixAct, int *minaX, int *minaY);

//combat.c
void combat(monstre *m, character *a, monde monde, int *invin, int sourisX, int sourisY, input *input);
void game_over(character *a, monde monde, SDL_Surface *screen, int *inc);
