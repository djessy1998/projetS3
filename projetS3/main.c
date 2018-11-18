#include <SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "perlin.h"
#include "fonction.h"
#include "fonctions_fichiers.h"
#include "creator.h"
#include <time.h>



void HandleEvent(SDL_Event event, input *i){
  fonction_Handle_Event(event, i);
}

int main(int argc,char* argv[])
{
  srand(time(NULL));
  input input;
  monde monde;
  character joueur1;

  creer_joueur(&joueur1);
  creer_monde(&monde);
  creer_input(&input);

  //Si on ajoute un argument on "affiche" l'aléatoire du terrain avec Perlin
  if(argv[1] != NULL){
    if(atoi(argv[1]) !=0){
      gen_monde(&monde, atoi(argv[1]));
      //Fait apparaitre le joueur sur une position haute (pas maximale) si il y a eu génération de terrain aléatoire
      joueur1.yMonde = TMONDE*TAILLE_BLOCS - NBBLOCS_FENETREY*TAILLE_BLOCS;
      joueur1.yMondeDouble = (double)joueur1.yMonde;
    }
  }

  Liste *listeItems = initialisation();
  insertion(listeItems, 1, 500, 128);
  insertion(listeItems, 2, 450, 10);
  insertion(listeItems, 2, 550, 10);

  SDL_Surface *screen;
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);

  /*Initialise SDL_ttf*/
  TTF_Init();

  /* set the title bar */
  SDL_WM_SetCaption("StarBund", "StarBund");

  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

  /* set keyboard repeat */
  SDL_EnableKeyRepeat(10, 10);

  /*Création de textures*/
  SDL_Surface* vieEnt = creer_texture("Sprites/heart.bmp");
  SDL_Surface* miVie = creer_texture("Sprites/Miheart.bmp");
  SDL_Surface* noVie = creer_texture("Sprites/Noheart.bmp");
  SDL_Surface* bg = creer_texture("Sprites/fond-nuage.bmp");
  SDL_Surface* casque = creer_texture("Sprites/casque.bmp");
  SDL_Surface* armure = creer_texture("Sprites/armure.bmp");
  SDL_Surface* character = creer_texture("Sprites/character.bmp");
  SDL_Surface* characterD = creer_texture("Sprites/characterD.bmp");
  SDL_Surface* terre = creer_texture("Sprites/terre.bmp");
  SDL_Surface* invIm = creer_texture("Sprites/Inv.bmp");
  SDL_Surface* ActuelInv = creer_texture("Sprites/Actuel.bmp");

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

  SDL_Rect posFond;

  posFond.x = 0;
  posFond.y = 0;


  int murG, murD = 0;
  int incrementAnim = 0;
  int touche = 0;
  int ItemAffich = 0, droite = 0, gauche = 0;
  int yMomTomb = 0, fait = 0, faitCalc = 0, yMomTombDeb = 0;
  Uint32 colorkey = SDL_MapRGB(character->format,0,0,0);
  Uint32 colorkeyVie = SDL_MapRGB(vieEnt->format,0,0,255);

  SDL_SetColorKey(character,SDL_SRCCOLORKEY,colorkey);
  SDL_SetColorKey(casque,SDL_SRCCOLORKEY,colorkey);
  SDL_SetColorKey(armure,SDL_SRCCOLORKEY,colorkey);
  SDL_SetColorKey(vieEnt,SDL_SRCCOLORKEY,colorkeyVie);
  SDL_SetColorKey(invIm,SDL_SRCCOLORKEY,colorkeyVie);
  SDL_SetColorKey(ActuelInv,SDL_SRCCOLORKEY,colorkeyVie);
  SDL_SetColorKey(miVie,SDL_SRCCOLORKEY,colorkeyVie);
  SDL_SetColorKey(noVie,SDL_SRCCOLORKEY,colorkeyVie);
  SDL_SetColorKey(characterD,SDL_SRCCOLORKEY,colorkey);

  int actualTime = 0;
  int lastTimes = 0;

  while(!input.data.quit)
    {

      //Compteur d'images par secondes
      actualTime = SDL_GetTicks();
      float dt = (actualTime - lastTimes);
      if(dt < 1000.0 / 144.0 ){
        SDL_Delay((1000.0 / 144.0) - dt); //On limite les images par secondes en faisant des pauses entre chaque image
      }
      lastTimes = SDL_GetTicks();
      //Compteur d'images par secondes

      SDL_Event event;

      if (SDL_PollEvent(&event)) {
	HandleEvent(event, &input);
      }

      SDL_BlitSurface(bg, NULL, screen, &posFond);

      affichage_monde(monde, joueur1, terre, screen);

      traitement_input(input, &joueur1, murG, murD, gauche, droite, listeItems, ItemAffich, &joueurAnimD, &joueurAnim, &incrementAnim);

      affichage_barre_inv(invIm, screen, &input, casque, armure, ActuelInv);

      traitement_input_inv(&input, invIm, casque, armure, screen, &joueur1, listeItems, ItemAffich);

      affichage_items_inv(input, casque, armure, screen);

      terreRonde(&joueur1, &murD, &murG);

      collision(&joueur1, monde.affichage, monde.posB, monde.posBY, &murD, &murG, &yMomTomb, &fait, &faitCalc, &yMomTombDeb, &touche);

      calc_vie_tombe(&joueur1, &yMomTombDeb, &faitCalc, &touche);

      afficherElementsListe(listeItems, &ItemAffich, &joueur1, screen, casque, armure, input.data.q , input.data.d, &monde);

      collisionIt(listeItems,monde.posBY,monde.posB, monde, ItemAffich);

      affichage_personnage(joueur1, characterD, character, &joueurAnimD, &joueurAnim, screen);

      affichage_vie_personnage(&joueur1, vieEnt, miVie, noVie, screen);

      SDL_UpdateRect(screen, 0, 0, 0, 0);
    }


  SDL_FreeSurface(bg);
  SDL_FreeSurface(terre);
  SDL_FreeSurface(casque);
  SDL_FreeSurface(armure);
  SDL_FreeSurface(character);
  SDL_FreeSurface(characterD);
  SDL_FreeSurface(invIm);
  SDL_FreeSurface(ActuelInv);
  SDL_FreeSurface(vieEnt);
  SDL_FreeSurface(miVie);
  SDL_FreeSurface(noVie);

  TTF_Quit();

  SDL_Quit();


  desallouer_tab_2D_int(monde.grilleInt, TMONDE);
  desallouer_tab_2D_char(monde.grilleChar, TMONDE);
  desallouer_tab_2D_int(monde.posB, TMONDE);
  desallouer_tab_2D_int(monde.posBY,TMONDE);
  desallouer_tab_2D_int(monde.affichage, NBBLOCS_FENETREY);
  //désallocation du pseudo du joueur:
  free(joueur1.nom);
  return 0;
}
