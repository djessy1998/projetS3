#include <SDL.h>
#include "fonction.h"

void HandleEvent(SDL_Event event, int *quit, int *z, int *q, int *s, int *d, int *e)
{
  switch (event.type) {
    /* close button clicked */
  case SDL_QUIT:
    *quit = 1;
    break;
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
      *quit = 1;
      break;
    case SDLK_z:
      *z = 1;
      break;
    case SDLK_q:
      *q = 1;
      break;
    case SDLK_s:
      *s = 1;
      break;
    case SDLK_d:
      *d = 1;
      break;
    case SDLK_e:
      if(*e == 0)
      {
      	*e = 1;
      	SDL_Delay(80);
      }
      else
      {
      	*e = 0;
      	SDL_Delay(80);
      }
    default:
      break;
    }
    break;
  case SDL_KEYUP:
    switch(event.key.keysym.sym){
    case SDLK_z:
      *z = 0;
      break;
    case SDLK_q:
      *q = 0;
      break;
    case SDLK_s: 
      *s = 0;
      break;
    case SDLK_d:
      *d = 0;
      break;
    default:
      break;
    }
    break;
  }
}
   
int main(int argc,char* argv[])
{

  int i,j;
  int grille[TMONDE][TMONDE];
  int posB[TMONDE][TMONDE];
  int posBY[TMONDE][TMONDE];
  int affichage[NBBLOCS_FENETREY][NBBLOCS_FENETREX];
  objet inv[4][10];

  float x_saut = -50;
  float y_saut = 0;
  for(i=0;i<TMONDE;i++)
    {
      for(j=0;j<TMONDE;j++)
        {
          grille[i][j] = VIDE;
        }
    }

    for(i=TMONDE-20;i<TMONDE;i++)
    {
      for(j=0;j<TMONDE;j++)
        {
          grille[i][j] = TERRE;
        }
    }
    
    /*Creation d'un trou de x cases*/
    for(i=0; i<3; i++)
    {
      grille[80+i][49] = VIDE;
      grille[80+i][51] = VIDE;
      grille[80+i][50] = VIDE;
    }
    
    grille[81][93] = VIDE;
    grille[81][92] = VIDE;
    grille[81][94] = VIDE;
  
    grille[80][92] = VIDE;
    grille[80][94] = VIDE;
  character joueur1 = {"Jean", 100, 0};
  joueur1.pos.x = 352;
  joueur1.pos.y = 400 - PLAYER_HEIGHT;
  joueur1.xMonde = (TMONDE*TAILLE_BLOCS)/2+7;
  joueur1.yMonde = 500;
  int xMondeB = 0;
  int yMondeB = 0;
  float forcegrav = (float)joueur1.pos.y;
  float vitesse = (float)joueur1.xMonde;
  
  SDL_Surface *screen, *temp, *bg, *terre, *character, *invIm;
  
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);

  /* set the title bar */
  SDL_WM_SetCaption("StarBund", "StarBund");

  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

  /* set keyboard repeat */
  SDL_EnableKeyRepeat(10, 10);

  temp = SDL_LoadBMP("Sprites/fond-nuage.bmp");
  bg = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  temp = SDL_LoadBMP("Sprites/character.bmp");
  character = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  temp = SDL_LoadBMP("Sprites/terre.bmp");
  terre = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  temp = SDL_LoadBMP("Sprites/Inv.bmp");
  invIm = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  SDL_Rect posFond;
    
  posFond.x = 0;
  posFond.y = 0;

  int gameover = 0;
  int z,q,s,d,e = 0;
  int bloquerG = 0;
  int bloquerD = 0;
  int murG,murD = 0;
  int saut = 1;

  while(!gameover)
    {
      SDL_Event event;



      if (SDL_PollEvent(&event)) {
	HandleEvent(event, &gameover, &z, &q, &s, &d, &e);
      }

    SDL_BlitSurface(bg, NULL, screen, &posFond);

    xMondeB = joueur1.xMonde/TAILLE_BLOCS;
    yMondeB = TMONDE - joueur1.yMonde/TAILLE_BLOCS - NBBLOCS_FENETREY;
    int decalageX = -joueur1.xMonde%TAILLE_BLOCS;
    int decalageY = -joueur1.yMonde%TAILLE_BLOCS;

   if(z == 1)
	{
	  if (saut){
		SDL_Delay(10);
		sauter(&joueur1, &saut, &x_saut, &y_saut, bloquerG, bloquerD);
	  }
	}
  if(d == 1)
	{
    if(bloquerD == 0)
    {
      deplacerD(&joueur1, &vitesse, murD, &murG);
    }
	}
      if(s == 1)
	{
	  baisser(&joueur1);
	}
      if(q == 1)
	{
	  if(bloquerG == 0)
	    {
	      deplacerG(&joueur1, &vitesse, murG, &murD);
	    }
	}
	if(e == 1)
	{
		SDL_Rect posInv;
		posInv.x = 50;
		posInv.y = 50;
		SDL_BlitSurface(invIm, NULL, screen, &posInv);
	}
      grille[joueur1.yMonde/TAILLE_BLOCS][joueur1.xMonde/TAILLE_BLOCS]=TERRE;
      for(i=0;i<NBBLOCS_FENETREY;i++ )
      {
        for(j=0;j<NBBLOCS_FENETREX;j++)
        {
	  affichage[i][j] = grille[i+yMondeB][j+xMondeB];
	  posB[i][j] = TAILLE_BLOCS*(j+xMondeB);
          posBY[i][j] = TAILLE_BLOCS*(joueur1.yMonde/TAILLE_BLOCS + NB_BLOCS_AU_DESSUS_JOUEUR - i);
	}
      }
      

      for(i=0;i<NBBLOCS_FENETREY;i++)
      {
       	 for(j=0;j<NBBLOCS_FENETREX;j++)
       	 {
	 	 if(affichage[i][j] == TERRE)
	    	{
		      SDL_Rect posGrille;
		      posGrille.x = j*TAILLE_BLOCS + decalageX;
		      posGrille.y = i*TAILLE_BLOCS + decalageY;
		      SDL_BlitSurface(terre, NULL, screen, &posGrille);
	    	}
        }
      }
      
      terreRonde(&xMondeB, &joueur1, &murD, &murG);

      collision(&joueur1, affichage, &forcegrav, &bloquerG, &bloquerD, posB, posBY, &saut);

      SDL_BlitSurface(character, NULL, screen, &joueur1.pos);

      SDL_UpdateRect(screen, 0, 0, 0, 0);    
    }

  SDL_FreeSurface(bg);
  SDL_FreeSurface(terre);

  SDL_Quit();

  return 0;
}
