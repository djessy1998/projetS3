#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include "fonctions_fichiers.h"

void HandleEvent(SDL_Event event, input *i){
  fonction_Handle_Event(event, i);
}

int main(int argc,char* argv[])
{
  
  SDL_Init(SDL_INIT_VIDEO);
  
  input input;
  monde monde;
  character joueur1 = {"Jean", 100, 0};

  monde.grilleChar = lire_fichier("saves/Monde1.txt");
  monde.grilleInt = allouer_tab_2D_int(TMONDE, TMONDE);
  tab_char2int(monde.grilleChar, monde.grilleInt, TMONDE, TMONDE);
  desallouer_tab_2D_char(monde.grilleChar, TMONDE);


  monde.posB = allouer_tab_2D_int(TMONDE, TMONDE);
  monde.posBY = allouer_tab_2D_int(TMONDE, TMONDE);
  monde.affichage = allouer_tab_2D_int(NBBLOCS_FENETREY, NBBLOCS_FENETREX);

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
  input.data.inv[0][1].type = 2;
  input.data.inv[0][2].type = 1;
  input.data.inv[0][3].type = 2;

  joueur1.pos.x = 352;
  joueur1.pos.y = 400 - PLAYER_HEIGHT;
  joueur1.pos.h = 58;
  joueur1.pos.w = 27;
  joueur1.xMonde = (TMONDE*TAILLE_BLOCS)/2+7;
  joueur1.yMonde = 100;
  joueur1.PV = 100;
  joueur1.PM = 100;
  joueur1.x_saut = -154.;
  joueur1.y_saut = 0.;
  joueur1.yMondeDouble = (double)joueur1.pos.y;
  joueur1.xMondeDouble = (double)joueur1.xMonde;
  joueur1.xPosBloquageDouble = (double)joueur1.pos.x;
  joueur1.dir = 1;
  joueur1.bloqAGauche = 0;
  joueur1.bloqADroite = 0;

  SDL_Surface *bg, *terre, *character, *invIm, *casque, *characterD, *armure;

  SDL_Window *fenetre;
  fenetre = SDL_CreateWindow("StarBund", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,0);

  SDL_Renderer *renderer = NULL;
  renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_TARGETTEXTURE);

  /* set keyboard repeat */
  //SDL_EnableKeyRepeat(10, 10);

  bg = SDL_LoadBMP("Sprites/fond-nuage.bmp");
  SDL_Texture *bgTexture;
  bgTexture = SDL_CreateTextureFromSurface(renderer,bg);

  casque = SDL_LoadBMP("Sprites/casque.bmp");
  SDL_Texture *casqueTexture;
  casqueTexture = SDL_CreateTextureFromSurface(renderer,casque);

  armure = SDL_LoadBMP("Sprites/armure.bmp");
  SDL_Texture *armureTexture;
  armureTexture = SDL_CreateTextureFromSurface(renderer, armure);
  
  character = SDL_LoadBMP("Sprites/character.bmp");
  SDL_SetColorKey(character,SDL_TRUE,SDL_MapRGB(character->format, 0, 0, 0));
  SDL_Texture *characterTexture;
  characterTexture = SDL_CreateTextureFromSurface(renderer,character);

  characterD = SDL_LoadBMP("Sprites/characterD.bmp");
  SDL_SetColorKey(characterD,SDL_TRUE,SDL_MapRGB(characterD->format, 0, 0, 0));
  SDL_Texture *characterDTexture;
  characterDTexture = SDL_CreateTextureFromSurface(renderer,characterD);

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

  terre = SDL_LoadBMP("Sprites/terre.bmp");
  SDL_Texture *terreTexture;
  terreTexture = SDL_CreateTextureFromSurface(renderer,terre);
  
  invIm = SDL_LoadBMP("Sprites/Inv.bmp");
  SDL_Texture *invImTexture;
  invImTexture = SDL_CreateTextureFromSurface(renderer,invIm);

  SDL_Rect posFond;
  posFond.x = 0;
  posFond.y = 0;
  posFond.h = 560;
  posFond.w = 720;

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
  int murG,murD, murH = 0;
  int saut = 1;
  int a = 0;
  int ItemAffich = 0, droite = 0, gauche = 0;
 
  while(!input.data.quit)
    {
      SDL_Event event;
      SDL_Rect posInv;
      posInv.h = 32;
      posInv.w = 32;
      SDL_Rect posItemsInv;
      posItemsInv.h = 24;
      posItemsInv.w = 28;

      if (SDL_PollEvent(&event)) {
	HandleEvent(event, &input);
      }
      

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,bgTexture, NULL, &posFond);

    int xAffichageStart = joueur1.xMonde/TAILLE_BLOCS;
    int yAffichageStart = TMONDE - joueur1.yMonde/TAILLE_BLOCS - NBBLOCS_FENETREY;
    int decalageX = -joueur1.xMonde%TAILLE_BLOCS;
    int decalageY = -joueur1.yMonde%TAILLE_BLOCS;

   if(input.data.z == 1)
	{
	  if (saut){
	  	SDL_Delay(10);
		sauter(&joueur1, &saut);
	  }
	}
  if(input.data.d == 1)
	{
	droite = 1;
	collisionItems(listeItems, ItemAffich, &joueur1, gauche, droite, murG, murD);
    if(joueur1.bloqADroite == 0)
    {
      deplacerD(&joueur1, murD, murG);
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
	joueur1.dir = 2;
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
	  collisionItems(listeItems, ItemAffich, &joueur1, gauche, droite, murG, murD);
	  if(joueur1.bloqAGauche == 0)
	    {
	      deplacerG(&joueur1,murG, murD);
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
	joueur1.dir = 1;
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
	SDL_RenderCopy(renderer,invImTexture, NULL, &posInv);
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
		 SDL_RenderCopy(renderer,casqueTexture, NULL, &posItemsInv);
           }
           else if(input.data.inv[i][j].type == 2)
           {
		 SDL_RenderCopy(renderer,armureTexture, NULL, &posItemsInv);
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
	    monde.affichage[i][j] = monde.grilleInt[i+yAffichageStart][j+xAffichageStart];
	    monde.posB[i][j] = TAILLE_BLOCS*(j+xAffichageStart);
	    monde.posBY[i][j] = TAILLE_BLOCS*(joueur1.yMonde/TAILLE_BLOCS + NB_BLOCS_AU_DESSUS_JOUEUR - i);
	    if(monde.affichage[i][j] == TERRE)
	      {
		SDL_Rect posGrille;
		posGrille.x = j*TAILLE_BLOCS + decalageX;
		posGrille.y = i*TAILLE_BLOCS + decalageY;
		posGrille.h = 16;
		posGrille.w = 16;
		SDL_RenderCopy(renderer,terreTexture, NULL, &posGrille);
	      }
	     }
      }

      if(input.data.numItemInvX != -1 && input.data.rien == 0)
      {
      	if(input.data.typeMemoire == 1)
      	{
		SDL_RenderCopy(renderer,casqueTexture, NULL, &input.data.posImage);
      	}
      	else if(input.data.typeMemoire == 2)
      	{
	    SDL_RenderCopy(renderer,armureTexture, NULL, &input.data.posImage);
      	}
      }

      terreRonde(&joueur1, &murD, &murG, &murH);

      collision(&joueur1, monde.affichage, monde.posB, monde.posBY, &saut, &murD);

      afficherElementsListe(listeItems, &ItemAffich, &joueur1, renderer, casqueTexture, armureTexture, input.data.q , input.data.d, &monde);

      if(joueur1.dir == 2)
      {
		SDL_RenderCopy(renderer,characterDTexture, &joueurAnimD, &joueur1.pos);
      }
      else if(joueur1.dir == 1)
      {
		SDL_RenderCopy(renderer,characterTexture, &joueurAnim, &joueur1.pos);
      }
      SDL_RenderPresent(renderer);
    }

  SDL_FreeSurface(bg);
  SDL_FreeSurface(terre);
  SDL_FreeSurface(casque);
  SDL_FreeSurface(armure);
  SDL_FreeSurface(character);
  SDL_FreeSurface(characterD);
  SDL_FreeSurface(invIm);
  SDL_DestroyTexture(bgTexture);
  SDL_DestroyTexture(terreTexture);
  SDL_DestroyTexture(casqueTexture);
  SDL_DestroyTexture(armureTexture);
  SDL_DestroyTexture(characterTexture);  
  SDL_DestroyTexture(characterDTexture);
  SDL_DestroyTexture(invImTexture);
  
  SDL_Quit();


  desallouer_tab_2D_int(monde.grilleInt, TMONDE);
  
  desallouer_tab_2D_int(monde.posB, TMONDE);
  desallouer_tab_2D_int(monde.posBY,TMONDE);
  desallouer_tab_2D_int(monde.affichage, NBBLOCS_FENETREY);
  return 0;
}
