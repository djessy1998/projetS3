#include "creator.h"
#include "atlas.h"


atlas* creer_atlas(image** tabIm){
  atlas* atlasJeu = malloc(sizeof(atlas));
  int i;
  for(i=0;i<NBIMAGES;i++){
    atlasJeu->tabIm[i] = tabIm[i];
  }
  free(tabIm);
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
  SDL_SetColorKey(Image_Monstre->surface,SDL_SRCCOLORKEY,colorkeyVie);
  tabIm[16] = Image_Monstre;

  image* fond_grotte = creer_texture("Sprites/fond_grotte.bmp",0, 0, 44, 44, 16, 16);
  SDL_SetColorKey(fond_grotte->surface,SDL_SRCCOLORKEY,colorkeyVie);
  tabIm[17] = fond_grotte;

  image* terre = creer_texture("Sprites/terre.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(terre->surface,SDL_SRCCOLORKEY,colorkey);
  tabIm[18] = terre;

  image* bg = creer_texture("Sprites/fond-nuage.bmp",0, 0, 0, 0, 0, 0);
  tabIm[19] = bg;

  image* vieM = creer_texture("Sprites/heartM.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(vieM->surface,SDL_SRCCOLORKEY,colorkeyVie);
  tabIm[20] = vieM;

  image* miVieM = creer_texture("Sprites/MiheartM.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(miVieM->surface,SDL_SRCCOLORKEY,colorkeyVie);
  tabIm[21] = miVieM;

  image* noVieM = creer_texture("Sprites/NoheartM.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(noVieM->surface,SDL_SRCCOLORKEY,colorkeyVie);
  tabIm[22] = noVieM;

  image* terrePS = creer_texture("Sprites/terrePS.bmp",0, 0, 0, 0, 0, 0);
  tabIm[23] = terrePS;

  image* nuage = creer_texture("Sprites/Cloud.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(nuage->surface,SDL_SRCCOLORKEY,colorkey);
  tabIm[24] = nuage;

  image* nuage1 = creer_texture("Sprites/Cloud1.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(nuage1->surface,SDL_SRCCOLORKEY,colorkey);
  tabIm[25] = nuage1;

  image* nuage2 = creer_texture("Sprites/Cloud2.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(nuage2->surface,SDL_SRCCOLORKEY,colorkey);
  tabIm[26] = nuage2;

  image* nuage3 = creer_texture("Sprites/Cloud3.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(nuage3->surface,SDL_SRCCOLORKEY,colorkey);
  tabIm[27] = nuage3;

  image* herbe = creer_texture("Sprites/herbe.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(herbe->surface,SDL_SRCCOLORKEY,colorkey);
  tabIm[28] = herbe;

  image* herbe1 = creer_texture("Sprites/herbe1.bmp",0, 0, 0, 0, 0, 0);
  SDL_SetColorKey(herbe1->surface,SDL_SRCCOLORKEY,colorkey);
  tabIm[29] = herbe1;

  image* terre1 = creer_texture("Sprites/Terre1.bmp",0, 0, 0, 0, 0, 0);
  tabIm[30] = terre1;

  image* terre2 = creer_texture("Sprites/Terre2.bmp",0, 0, 0, 0, 0, 0);
  tabIm[31] = terre2;

  image* terre3 = creer_texture("Sprites/Terre3.bmp",0, 0, 0, 0, 0, 0);
  tabIm[32] = terre3;

  return creer_atlas(tabIm);
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

void setPosH(image* image, int h){
 image->pos.h = h;
}

void setPosW(image* image, int w){
 image->pos.w = w;
}
