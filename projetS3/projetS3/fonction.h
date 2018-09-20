#include <SDL.h>

#define SCREEN_WIDTH   720
#define SCREEN_HEIGHT  560
#define PLAYER_WIDTH   20
#define PLAYER_HEIGHT  40
#define FORCE_GRA      0.2
#define VITESSE        0.5
#define VITESSEJ	   0.2
#define TMONDE         100
#define NBBLOCS_FENETREX 47
#define NBBLOCS_FENETREY 35
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
  
};

typedef struct objet objet;
struct objet
{
	int type;
	char nom[10];
	int qqc;
};

void deplacerG(character *a, float *vitesse, int murGau, int *murDro);
void deplacerD(character *a, float *vitesse, int murDro, int *murGau);
void gravite(character *a, float *force);
void collision(character *a, int affichage[NBBLOCS_FENETREY][NBBLOCS_FENETREX], float *force,int *bloquerG, int *bloquerD, int posB[NBBLOCS_FENETREY][NBBLOCS_FENETREX - 2]);
void sauter(character *a, double vx, double *vy, double *vgrav);
void baisser(character *a);
void terreRonde(int *xMondeBl, character *a, int *murDro, int *murGau);
