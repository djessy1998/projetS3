#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include "fonctions_fichiers.h"

void HandleEvent(SDL_Event event, int *quit, int *z, int *q, int *s, int *d, int *e, int *f, int *butdown, int *numItemInvX, int *numItemInvY, SDL_Rect *posImage, int i, int j, int *n, items inve[4][10], int *supprimer, int *getB, int *rien, int typeMemoire)
{
  switch (event.type) {
    /* close button clicked */
  case SDL_QUIT:
    *quit = 1;
    break;
  case SDL_MOUSEBUTTONDOWN:
     if (event.button.button == SDL_BUTTON_LEFT)
    {
      *butdown = 1;
    }
    break;
  case SDL_MOUSEBUTTONUP:
    if (event.button.button == SDL_BUTTON_LEFT)
    {
      *butdown = 0;
    }
    break;
  case SDL_MOUSEMOTION:
    for(i = 0; i < 4; i++)
    {
      for(j = 0; j < 10; j++)
      {
        if(((*butdown == 1) && ((event.motion.x >= 52 + (33 * j) && event.motion.x <= 52 + 32 + (33 * j)) && (event.motion.y >= 54 + (33 * i) && event.motion.y <= 54 + 32 + (33 * i))) && (*e == 1)))
        {
	  if(*getB == 0)
          {
            *numItemInvY = i;
            *numItemInvX = j;
            *getB = 1;
          }
          if((*butdown == 1) && inve[*numItemInvY][*numItemInvX].type == -2)
          {
            inve[*numItemInvY][*numItemInvX].type = -1;
            *rien = 1;
          }
          if(*rien == 0)
          {
            posImage->x = event.motion.x - 16;
            posImage->y = event.motion.y - 16;
          }
        }
        if((*butdown == 1) && ((event.motion.x <= 52 || event.motion.x >= 52 + 32) && (event.motion.y <= 54 || event.motion.y >= 54 + 32)) && (*e == 1))
        {
          if(*rien == 0)
          {
            posImage->x = event.motion.x - 16;
            posImage->y = event.motion.y - 16;
          }
        }
        if((*butdown == 0) && ((event.motion.x >= 50 && event.motion.x <= 50 + (33*10)) && (event.motion.y >= 50 && event.motion.y <= 50 + (33 * 4))) && (*e == 1))
        {
          if(*numItemInvX != -1 && *numItemInvY != -1)
          {
	    if(*rien == 0)
	    {
	      TrierInv(*rien, inve, typeMemoire);
	    }
            *numItemInvX = -1;
            *numItemInvY = -1;
            *supprimer = 0;
            *getB = 0;
	    	*rien = 0;
          }
        }
        else if((*butdown == 0) && ((event.motion.x <= 52 || event.motion.x >= 52 + 32) && (event.motion.y <= 54 || event.motion.y >= 54 + 32)) && (*e == 1))
        {
          if(*numItemInvX != -1 && *numItemInvY != -1)
          {
            posImage->x = -300;
            posImage->y = -300;
            *numItemInvX = -1;
            *numItemInvY = -1;
            *supprimer = 0;
            *getB = 0;
          }
        }
      }
    }
    break;
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
      *quit = 1;
      break;
    case SDLK_z:
      *z = 1;
      break ;
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
    case SDLK_f:
      *f = 1;
      break;
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
    case SDLK_f:
      *f = 0;
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

  char** grilleTest;
  grilleTest = lire_fichier("saves/Monde1.txt");

  int** grilleInt = allouer_tab_2D_int(TMONDE, TMONDE);
  tab_char2int(grilleTest, grilleInt, TMONDE, TMONDE);
  int posB[TMONDE][TMONDE];
  int posBY[TMONDE][TMONDE];
  int affichage[NBBLOCS_FENETREY][NBBLOCS_FENETREX];
  items inv[4][10];
  float x_saut = -154.;
  float y_saut = 0.;
  Liste *listeItems = initialisation();
  insertion(listeItems, 1, 500, 128);
  insertion(listeItems, 2, 450, 128);
  for(i=0;i<4;i++)
    {
      for(j=0;j<10;j++)
        {
          inv[i][j].type = -1;
        }
    }

  inv[0][0].type = 1;
  inv[0][1].type = 1;
  inv[0][2].type = 1;
  inv[0][3].type = 2;

  character joueur1 = {"Jean", 100, 0};
  joueur1.pos.x = 352;
  joueur1.pos.y = 400 - PLAYER_HEIGHT;
  joueur1.xMonde = (TMONDE*TAILLE_BLOCS)/2+7;
  joueur1.yMonde = 500;
  joueur1.PV = 100;
  joueur1.PM = 100;
  int xMondeB = 0;
  int yMondeB = 0;
  float forcegrav = (float)joueur1.pos.y;
  float vitesse = (float)joueur1.xMonde;
  float vitesseFloat = (float)joueur1.pos.x;

  SDL_Surface *screen, *temp, *bg, *terre, *character, *invIm, *casque, *characterD, *armure;

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

  temp = SDL_LoadBMP("Sprites/casque.bmp");
  casque = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  temp = SDL_LoadBMP("Sprites/armure.bmp");
  armure = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  temp = SDL_LoadBMP("Sprites/character.bmp");
  character = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  temp = SDL_LoadBMP("Sprites/characterD.bmp");
  characterD = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  SDL_Rect joueurAnim;
  joueurAnim.x = 7;
  joueurAnim.y = 0;
  joueurAnim.h = 58;
  joueurAnim.w = 27;

  SDL_Rect joueurAnimD;
  joueurAnimD.x = 7;
  joueurAnimD.y = 0;
  joueurAnimD.h = 58;
  joueurAnimD.w = 27;

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
  int z,q,s,d,e,f = 0;
  int bloquerG = 0;
  int bloquerD = 0;
  int murG,murD = 0;
  int saut = 1;
  int buttonDown = 0;
  int numItemInven = -1;
  int numItemInvenY = -1;
  int k = 0,l = 0,n = 0, a = 0;
  int supprimer = 0, getBInv= 0, rienI = 0, dirChar = 1;
  int typeMemor = 0, ItemAffich = 0, droite = 0, gauche = 0;
  Uint32 colorkey = SDL_MapRGB(character->format,0,0,0);
  SDL_SetColorKey(character,SDL_SRCCOLORKEY,colorkey);
  SDL_SetColorKey(characterD,SDL_SRCCOLORKEY,colorkey);

  while(!gameover)
    {
      SDL_Event event;
      SDL_Rect posInv;
      SDL_Rect posItemsInv;
      SDL_Rect posImage;

      if (SDL_PollEvent(&event)) {
	HandleEvent(event, &gameover, &z, &q, &s, &d, &e, &f, &buttonDown, &numItemInven,&numItemInvenY, &posImage, k, l, &n, inv, &supprimer, &getBInv, &rienI, typeMemor);
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
	droite = 1;
	collisionItems(listeItems, dirChar, ItemAffich, bloquerG, bloquerD, &joueur1, gauche, droite, murG, murD);
    if(bloquerD == 0)
    {
      deplacerD(&joueur1, &vitesse, murD, murG, &vitesseFloat);
    }
    a += 2;
	if(a > 58)
	{
	  joueurAnimD.y += 58;
	  a = 0;
	}
	if (joueurAnimD.y > 800){
	 joueurAnimD.y = 0;
	}
	dirChar = 2;
	}
	else
	{
		droite = 0;
		joueurAnimD.y = 0;
	}
      if(s == 1)
	{
	  baisser(&joueur1);
	}
      if(q == 1)
	{
	  gauche = 1;
	  collisionItems(listeItems, dirChar, ItemAffich, bloquerG, bloquerD, &joueur1, gauche, droite, murG, murD);
	  if(bloquerG == 0)
	    {
	      deplacerG(&joueur1, &vitesse, murG, murD, &vitesseFloat);
	    }
	a += 2;
	if(a > 58)
	{
	  joueurAnim.y += 58;
	  a = 0;
	}
	if (joueurAnim.y > 800){
	 joueurAnim.y = 0;
	}
	dirChar = 1;
	}
	else
	{
	  gauche = 0;
	 joueurAnim.y = 0;
	}
	if(e == 1)
	{
    for(i = 0; i < 4; i++)
    {
      for(j = 0; j < 10; j++)
      {
        posInv.x = 50 + (33 * j);
        posInv.y = 50 + (33 * i);
        SDL_BlitSurface(invIm, NULL, screen, &posInv);
        if(numItemInven != -1 && supprimer == 0 && inv[numItemInvenY][numItemInven].type != -1)
        {
          typeMemor = inv[numItemInvenY][numItemInven].type;
          inv[numItemInvenY][numItemInven].type = -1;
	  	  supprimer = 1;
        }
        else if (numItemInven != -1 && supprimer == 0 && inv[numItemInvenY][numItemInven].type == -1)
        {
          inv[numItemInvenY][numItemInven].type = -2;
          supprimer = 1;
        }
        if(inv[i][j].type > -1)
        {
           posItemsInv.x = 50 + (33 * j) + 2;
           posItemsInv.y = 50 + (33 * i) + 4;
           if(inv[i][j].type == 1)
           {
           	 SDL_BlitSurface(casque, NULL, screen, &posItemsInv);
           }
           else if(inv[i][j].type == 2)
           {
           	 SDL_BlitSurface(armure, NULL, screen, &posItemsInv);
           }
        }
      }
    }
	}
  if(f == 1)
  {
    //RAMASSAGE ITEM
  }
      grilleInt[joueur1.yMonde/TAILLE_BLOCS][joueur1.xMonde/TAILLE_BLOCS]=TERRE;
      for(i=0;i<NBBLOCS_FENETREY;i++ )
      {
        for(j=0;j<NBBLOCS_FENETREX;j++)
        {
	         affichage[i][j] = grilleInt[i+yMondeB][j+xMondeB];
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
	               affichage[21][15] = VIDE;
	               affichage[22][15] = VIDE;
	               affichage[23][15] = VIDE;
	    	    }
        }
      }

      if(numItemInven != -1 && rienI == 0)
      {
      	if(typeMemor == 1)
      	{
			SDL_BlitSurface(casque, NULL, screen, &posImage);
      	}
      	else if(typeMemor == 2)
      	{
      		SDL_BlitSurface(armure, NULL, screen, &posImage);
      	}
      }

      terreRonde(&xMondeB, &joueur1, &murD, &murG);

      collision(&joueur1, affichage, &forcegrav, &bloquerG, &bloquerD, posB, posBY, &saut);

      afficherElementsListe(listeItems, &ItemAffich, dirChar, &joueur1,screen, casque, armure, q , d, bloquerG, bloquerD);

      if(dirChar == 2)
      {
		SDL_BlitSurface(characterD, &joueurAnimD, screen, &joueur1.pos);
      }
      else if(dirChar == 1)
      {
		SDL_BlitSurface(character, &joueurAnim, screen, &joueur1.pos);
      }

      SDL_UpdateRect(screen, 0, 0, 0, 0);
    }

    SDL_FreeSurface(bg);
    SDL_FreeSurface(terre);
    SDL_FreeSurface(casque);
    SDL_FreeSurface(armure);
    SDL_FreeSurface(character);
    SDL_FreeSurface(characterD);
    SDL_FreeSurface(invIm);

    SDL_Quit();

    desallouer_tab_2D_char(grilleTest, TMONDE);
    desallouer_tab_2D_int(grilleInt, TMONDE);

  return 0;
}
