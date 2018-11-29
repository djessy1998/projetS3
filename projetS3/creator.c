#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fonction.h"
#include "creator.h"
#include "perlin.h"
#include "fonctions_fichiers.h"

void creer_joueur(character *joueur){
  joueur->nom = (char*) malloc(4 *sizeof(char));
  strcpy(joueur->nom, "Jean");
  joueur->PV = FULL_VIE;
  joueur->PM = PM_START;
  joueur->pos.x = POSX_START;
  joueur->pos.y = POSY_START - PLAYER_HEIGHT;
  joueur->xMonde = (TMONDE*TAILLE_BLOCS)/2+7;
  joueur->yMonde = 100;
  joueur->velocity_y = VELOCITE_MAX;
  joueur->yMondeDouble = (double)joueur->yMonde;
  joueur->xMondeDouble = (double)joueur->xMonde;
  joueur->xPosBloquageDouble = (double)joueur->pos.x;
  joueur->yPosBloquageDouble = (double)joueur->pos.y;
  joueur->dir = 1;
  joueur->bloqAGauche = 0;
  joueur->bloqADroite = 0;
  joueur->autorisationSaut = 1;
}


void creer_monde(monde *monde){
  if(TMONDE == 100){
    monde->grilleChar = lire_fichier("saves/Monde1.txt");
  }else if(TMONDE == 1000){
    monde->grilleChar = lire_fichier("saves/Monde2.txt");
  }
  monde->grilleInt = allouer_tab_2D_int(TMONDE, TMONDE);
  tab_char2int(monde->grilleChar, monde->grilleInt, TMONDE, TMONDE);

  monde->posB = allouer_tab_2D_int(TMONDE, TMONDE);
  monde->posBY = allouer_tab_2D_int(TMONDE, TMONDE);
  monde->affichage = allouer_tab_2D_int(NBBLOCS_FENETREY, NBBLOCS_FENETREX);
}



void creer_input(input *input){
  int i;
  int j;
  //Remplis l'inventaire d'éléments vide
  for(i=0;i<4;i++)
    {
      for(j=0;j<10;j++)
	{
	  input->data.inv[i][j].type = -1;
	}
    }

  input->data.inv[0][0].type = 1;
  input->data.inv[0][1].type = 2;
  input->data.quit = 0;
  input->data.z = 0;
  input->data.q = 0;
  input->data.s = 0;
  input->data.d = 0;
  input->data.e = 0;
  input->data.f = 0;
  input->data.Un = 1;
  input->data.butDown = 0;
  input->data.numItemInvX = -1;
  input->data.numItemInvY = -1;
  input->data.n = 0;
  input->data.supprimer = 0;
  input->data.getB= 0;
  input->data.rien = 0;
  input->data.typeMemoire = 0;

  for(i=0;i<4;i++){
    for(j=0;j<10;j++){
      input->data.inv[i][j].nomItem = " ";
      if(input->data.inv[i][j].type == 1){
        input->data.inv[i][j].nomItem = "Casque";
      }
      if(input->data.inv[i][j].type == 2){
        input->data.inv[i][j].nomItem = "Armure";
      }
    }
  }
}

void creer_monstre(monstre *monstre, atlas* atlasJeu, monde monde){
  monstre->nom = (char*) malloc(5 *sizeof(char));
  strcpy(monstre->nom, "Slime");
  monstre->PV = 100;
  monstre->x = TMONDE/2;
  monstre->y = 0;

  while(monde.grilleInt[monstre->y][monstre->x] != TERRE){
    monstre->y += 1;
    if(monde.grilleInt[monstre->y][monstre->x+1] == TERRE && monde.grilleInt[monstre->y][monstre->x-1] == TERRE){
      monstre->x += 1;
      monstre->y = 0;
    }
  }
  setPosX(atlasJeu->Image_Monstre, 0);
  setPosY(atlasJeu->Image_Monstre, 0);
  setAnimX(atlasJeu->Image_Monstre, 0);
  setAnimY(atlasJeu->Image_Monstre, 2);
  setAnimH(atlasJeu->Image_Monstre, 22);
  setAnimW(atlasJeu->Image_Monstre, 32);
  monstre->x = TAILLE_BLOCS*monstre->x;
  monstre->y = TMONDE*TAILLE_BLOCS - TAILLE_BLOCS*monstre->y + 22; //22 est la hauteur du monstre
  monstre->velocity_y = 0;
}

atlas* creer_atlas(image** tabIm){
  atlas* atlasJeu = malloc(sizeof(atlas));
  atlasJeu->character = tabIm[0];
  atlasJeu->vieEnt = tabIm[1];
  atlasJeu->casque = tabIm[2];
  atlasJeu->armure = tabIm[3];
  atlasJeu->invIm = tabIm[4];
  atlasJeu->ActuelInv = tabIm[5];
  atlasJeu->miVie = tabIm[6];
  atlasJeu->noVie = tabIm[7];
  atlasJeu->Crack = tabIm[8];
  atlasJeu->characterD = tabIm[9];
  atlasJeu->tronc = tabIm[10];
  atlasJeu->abg = tabIm[11];
  atlasJeu->abd = tabIm[12];
  atlasJeu->topArb = tabIm[13];
  atlasJeu->basArb = tabIm[14];
  atlasJeu->map = tabIm[15];
  atlasJeu->Image_Monstre = tabIm[16];
  atlasJeu->fond_grotte = tabIm[17];
  atlasJeu->terre = tabIm[18];
  atlasJeu->bg = tabIm[19];
  return atlasJeu;
}

image* creer_texture(char* chemin, int x, int y, int animX, int animY, int animH, int animW){
  image* text = malloc(sizeof(image));
  text->surface = SDL_LoadBMP(chemin);
  text->pos.x = x;
  text->pos.y = y;
  text->anim.x = animX;
  text->anim.y = animY;
  text->anim.h = animH;
  text->anim.w = animW;
  return text;
}

int getPosX(image* image){
  return image->pos.x;
}

int getPosY(image* image){
  return image->pos.y;
}

void setPosX(image* image, int x){
  image->pos.x = x;
}

void setPosY(image* image, int y){
  image->pos.y = y;
}

void setAnimX(image* image, int x){
  image->anim.x = x;
}

void setAnimY(image* image, int y){
  image->anim.y = y;
}

void setAnimH(image* image, int h){
  image->anim.h = h;
}

void setAnimW(image* image, int w){
  image->anim.w = w;
}

void detruire_text(image* image){
  SDL_FreeSurface(image->surface);
  free(image);
  image = NULL;
}

atlas* init_atlas(){

  image** tabIm = malloc(sizeof(image*)*NBIMAGES);

  image* character = creer_texture("Sprites/character.bmp", POSX_START, POSY_START - PLAYER_HEIGHT, 7, 0, 58, 27);
  Uint32 colorkey = SDL_MapRGB(character->surface->format,0,0,0);
  SDL_SetColorKey(character->surface,SDL_SRCCOLORKEY,colorkey);
  tabIm[0] = character;

  image* vieEnt = creer_texture("Sprites/heart.bmp",0, 0, 0, 0, 0, 0);
  Uint32 colorkeyVie = SDL_MapRGB(vieEnt->surface->format,0,0,255);
  SDL_SetColorKey(vieEnt->surface,SDL_SRCCOLORKEY,colorkeyVie);
  tabIm[1] = vieEnt;

  image* casque = creer_texture("Sprites/casque.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(casque->surface,SDL_SRCCOLORKEY,colorkey);
  tabIm[2] = casque;

  image* armure = creer_texture("Sprites/armure.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(armure->surface,SDL_SRCCOLORKEY,colorkey);
  tabIm[3] = armure;

  image* invIm = creer_texture("Sprites/Inv.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(invIm->surface,SDL_SRCCOLORKEY,colorkeyVie);
  tabIm[4] = invIm;

  image* ActuelInv = creer_texture("Sprites/Actuel.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(ActuelInv->surface,SDL_SRCCOLORKEY,colorkey);
  tabIm[5] = ActuelInv;

  image* miVie = creer_texture("Sprites/Miheart.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(miVie->surface,SDL_SRCCOLORKEY,colorkeyVie);
  tabIm[6] = miVie;

  image* noVie = creer_texture("Sprites/Noheart.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(noVie->surface,SDL_SRCCOLORKEY,colorkeyVie);
  tabIm[7] = noVie;

  image* Crack = creer_texture("Sprites/Crack.bmp",0, 0, 15, 0, 15, 15);
  SDL_SetColorKey(Crack->surface,SDL_SRCCOLORKEY,colorkeyVie);
  tabIm[8] = Crack;

  image* characterD = creer_texture("Sprites/characterD.bmp",0, 0, 7, 0, 58, 27);
  SDL_SetColorKey(characterD->surface,SDL_SRCCOLORKEY,colorkey);
  tabIm[9] = characterD;

  image* tronc = creer_texture("Sprites/tronc.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(tronc->surface,SDL_SRCCOLORKEY,colorkey);
  tabIm[10] = tronc;

  image* abg = creer_texture("Sprites/abg.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(abg->surface,SDL_SRCCOLORKEY,colorkey);
  tabIm[11] = abg;

  image* abd = creer_texture("Sprites/abd.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(abd->surface,SDL_SRCCOLORKEY,colorkey);
  tabIm[12] = abd;

  image* topArb = creer_texture("Sprites/topArb.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(topArb->surface,SDL_SRCCOLORKEY,colorkey);
  tabIm[13] = topArb;

  image* basArb = creer_texture("Sprites/barb.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(basArb->surface,SDL_SRCCOLORKEY,colorkey);
  tabIm[14] = basArb;

  image* map = creer_texture("Sprites/MiniMapFrame.bmp",SCREEN_WIDTH - 216  - 10, 10, 0, 0, 0, 0);
  SDL_SetColorKey(map->surface,SDL_SRCCOLORKEY,colorkey);
  tabIm[15] = map;

  image* Image_Monstre = creer_texture("Sprites/slime.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(Image_Monstre->surface,SDL_SRCCOLORKEY,colorkey);
  tabIm[16] = Image_Monstre;

  image* fond_grotte = creer_texture("Sprites/fond_grotte.bmp",0, 0, 44, 44, 16, 16);
  SDL_SetColorKey(fond_grotte->surface,SDL_SRCCOLORKEY,colorkeyVie);
  tabIm[17] = fond_grotte;

  image* terre = creer_texture("Sprites/terre.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(terre->surface,SDL_SRCCOLORKEY,colorkey);
  tabIm[18] = terre;

  image* bg = creer_texture("Sprites/fond-nuage.bmp",0, 0, 0, 0, 0, 0);
  tabIm[19] = bg;

  return creer_atlas(tabIm);
}

SDL_Surface* creer_minimap(monde *monde){
  int i,j;
  SDL_Surface *temp = NULL;
  SDL_Color colors[256];
  //srand(0);
  for(i=0;i<256;i++){
      colors[i].r=rand()%256;
      colors[i].g=rand()%256;
      colors[i].b=rand()%256;
  }
  temp = SDL_CreateRGBSurface(SDL_SWSURFACE,200,200,8, 0xff, 0xff, 0xff, 0);
  Uint8 *p = temp->pixels;
  for(i=0;i<TMONDE;i+=5){
    for(j=0;j<TMONDE;j+=5){
      *p = monde->grilleInt[i][j];
      p++;
    }
  }
  SDL_SetPalette(temp,SDL_LOGPAL|SDL_PHYSPAL, colors, 0, 256);
  SDL_Surface* tex = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  return tex;
}
