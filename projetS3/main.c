#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include "fonctions_fichiers.h"

void HandleEvent(SDL_Event event, input *i){
  fonction_Handle_Event(event, i);
}

int main(int argc,char* argv[])
{
  input input;
  monde monde;

  monde.grilleChar = lire_fichier("saves/Monde1.txt");
  monde.grilleInt = allouer_tab_2D_int(TMONDE, TMONDE);
  tab_char2int(monde.grilleChar, monde.grilleInt, TMONDE, TMONDE);
  desallouer_tab_2D_char(monde.grilleChar, TMONDE);


  monde.posB = allouer_tab_2D_int(TMONDE, TMONDE);
  monde.posBY = allouer_tab_2D_int(TMONDE, TMONDE);
  monde.affichage = allouer_tab_2D_int(NBBLOCS_FENETREY, NBBLOCS_FENETREX);

  float x_saut = -154.;
  float y_saut = 0.;

  Liste *listeItems = initialisation();
  insertion(listeItems, 1, 500, 128);
  insertion(listeItems, 2, 450, 128); 

  for(int i=0;i<4;i++)
    {
      for(int j=0;j<10;j++)
        {
          input.data.inv[i][j].type = -1;
        }
    }

  input.data.inv[0][0].type = 1;
  input.data.inv[0][1].type = 1;
  input.data.inv[0][2].type = 1;
  input.data.inv[0][3].type = 2;

  character joueur1 = {"Jean", 100, 0};
  joueur1.pos.x = 352;
  joueur1.pos.y = 400 - PLAYER_HEIGHT;
  joueur1.xMonde = (TMONDE*TAILLE_BLOCS)/2+7;
  joueur1.yMonde = 100;
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

  input.data.quit = 0;
  input.data.z = 0;
  input.data.q = 0;
  input.data.s = 0;
  input.data.d = 0;
  input.data.e = 0;
  input.data.f = 0;
  input.data.butDown = 0;
  input.data.numItemInvX = -1;
  input.data.numItemInvY = -1;
  input.data.n = 0;
  input.data.supprimer = 0;
  input.data.getB= 0;
  input.data.rien = 0;
  input.data.typeMemoire = 0;
  int bloquerG = 0;
  int bloquerD = 0;
  int murG,murD, murH = 0;
  int saut = 1;
  int a = 0;
  int dirChar = 1;
  int ItemAffich = 0, droite = 0, gauche = 0;
  Uint32 colorkey = SDL_MapRGB(character->format,0,0,0);
  SDL_SetColorKey(character,SDL_SRCCOLORKEY,colorkey);
  SDL_SetColorKey(characterD,SDL_SRCCOLORKEY,colorkey);

  while(!input.data.quit)
    {
      SDL_Event event;
      SDL_Rect posInv;
      SDL_Rect posItemsInv;

      if (SDL_PollEvent(&event)) {
	HandleEvent(event, &input);
      }

    SDL_BlitSurface(bg, NULL, screen, &posFond);

    xMondeB = joueur1.xMonde/TAILLE_BLOCS;
    yMondeB = TMONDE - joueur1.yMonde/TAILLE_BLOCS - NBBLOCS_FENETREY;
    int decalageX = -joueur1.xMonde%TAILLE_BLOCS;
    int decalageY = -joueur1.yMonde%TAILLE_BLOCS;

   if(input.data.z == 1)
	{
	  if (saut){
		SDL_Delay(10);
		sauter(&joueur1, &saut, &x_saut, &y_saut, bloquerG, bloquerD);
	  }
	}
  if(input.data.d == 1)
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
      if(input.data.s == 1)
	{
	  baisser(&joueur1);
	}
      if(input.data.q == 1)
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
	if(input.data.e == 1)
	{
    for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 10; j++)
      {
        posInv.x = 50 + (33 * j);
        posInv.y = 50 + (33 * i);
        SDL_BlitSurface(invIm, NULL, screen, &posInv);
        if(input.data.numItemInvX != -1 && input.data.supprimer == 0 && input.data.inv[input.data.numItemInvY][input.data.numItemInvX].type != -1)
        {
          input.data.typeMemoire = input.data.inv[input.data.numItemInvY][input.data.numItemInvX].type;
          input.data.inv[input.data.numItemInvY][input.data.numItemInvX].type = -1;
	  	  input.data.supprimer = 1;
        }
        else if (input.data.numItemInvX != -1 && input.data.supprimer == 0 && input.data.inv[input.data.numItemInvY][input.data.numItemInvX].type == -1)
        {
          input.data.inv[input.data.numItemInvY][input.data.numItemInvX].type = -2;
          input.data.supprimer = 1;
        }
        if(input.data.inv[i][j].type > -1)
        {
           posItemsInv.x = 50 + (33 * j) + 2;
           posItemsInv.y = 50 + (33 * i) + 4;
           if(input.data.inv[i][j].type == 1)
           {
           	 SDL_BlitSurface(casque, NULL, screen, &posItemsInv);
           }
           else if(input.data.inv[i][j].type == 2)
           {
           	 SDL_BlitSurface(armure, NULL, screen, &posItemsInv);
           }
        }
      }
    }
	}
  if(input.data.f == 1)
  {
    //RAMASSAGE ITEM
  }

      for(int i=0;i<NBBLOCS_FENETREY;i++ )
      {
        for(int j=0;j<NBBLOCS_FENETREX;j++)
        {
	    monde.affichage[i][j] = monde.grilleInt[i+yMondeB][j+xMondeB];
	    monde.posB[i][j] = TAILLE_BLOCS*(j+xMondeB);
	    monde.posBY[i][j] = TAILLE_BLOCS*(joueur1.yMonde/TAILLE_BLOCS + NB_BLOCS_AU_DESSUS_JOUEUR - i);
	    if(monde.affichage[i][j] == TERRE)
	      {
		SDL_Rect posGrille;
		posGrille.x = j*TAILLE_BLOCS + decalageX;
		posGrille.y = i*TAILLE_BLOCS + decalageY;
		SDL_BlitSurface(terre, NULL, screen, &posGrille);
	      }
	}
      }

      if(input.data.numItemInvX != -1 && input.data.rien == 0)
      {
      	if(input.data.typeMemoire == 1)
      	{
			SDL_BlitSurface(casque, NULL, screen, &input.data.posImage);
      	}
      	else if(input.data.typeMemoire == 2)
      	{
      		SDL_BlitSurface(armure, NULL, screen, &input.data.posImage);
      	}
      }

      terreRonde(&xMondeB, &joueur1, &murD, &murG, &murH);

      collision(&joueur1, monde.affichage, &forcegrav, &bloquerG, &bloquerD, monde.posB, monde.posBY, &saut);

      afficherElementsListe(listeItems, &ItemAffich, dirChar, &joueur1,screen, casque, armure, input.data.q , input.data.d, bloquerG, bloquerD);

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


    desallouer_tab_2D_int(monde.grilleInt, TMONDE);

  return 0;
}
