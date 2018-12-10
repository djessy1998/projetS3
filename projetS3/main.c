#include <SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "perlin.h"
#include "fonction.h"
#include "fonctions_fichiers.h"
#include "creator.h"
#include <time.h>



void HandleEvent(SDL_Event event, input *i, character *a, monde *monde,int *incAnim, int *minaX, int *minaY, int *choixAct){
  fonction_Handle_Event(event, i, a, monde,incAnim, minaX, minaY, choixAct);
}

int main(int argc,char* argv[])
{
  srand(time(NULL));
  input input;
  monde monde;
  character joueur1;
  monstre monstre;

  int freq = 3;

  creer_joueur(&joueur1);
  creer_monde(&monde);
  creer_input(&input);

  SDL_Surface *screen;
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  SDL_WM_SetCaption("StarBund", "StarBund");
  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  /* set keyboard repeat */
  SDL_EnableKeyRepeat(10, 10);

  /*Création de textures*/
  atlas* atlasJeu = init_atlas();

  //On génère le monde avec l'algorithme de perlin
  gen_monde(&monde, freq);
  apparition_joueur(&joueur1, monde);
  creer_monstre(&monstre, atlasJeu, monde);

  SDL_Rect posMiniMap;

  posMiniMap.x = SCREEN_WIDTH - 208  - 10;
  posMiniMap.y = 18;
  posMiniMap.h = 100;
  posMiniMap.w = 100;

  int murG, murD = 0;
  int incrementAnim = 0;
  int touche = 0, incAnim = 0, minaX = 0, minaY = 0;
  int ItemAffich = 0, droite = 0, gauche = 0, choixAct;
  int yMomTomb = 0, fait = 0, faitCalc = 0, yMomTombDeb = 0;
  int actualTime = 0;
  int lastTimes = 0;
  int invin = 501;
  int inc = 0;

  Liste *listeItems = initialisation();

  ItemMonde(monde,listeItems);

  while(!input.data.quit){
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
      HandleEvent(event, &input, &joueur1, &monde,&incAnim,&minaX,&minaY,&choixAct);
    }

    SDL_BlitSurface(atlasJeu->tabIm[BGIM]->surface, NULL, screen, &atlasJeu->tabIm[BGIM]->pos);

    affichage_monde(monde, joueur1, atlasJeu, screen);

    SDL_Surface *miniMap = creer_minimap(&monde, &joueur1);

    SDL_BlitSurface(miniMap, NULL, screen, &posMiniMap);

    SDL_FreeSurface(miniMap);

    SDL_BlitSurface(atlasJeu->tabIm[MAPIM]->surface, NULL, screen, &atlasJeu->tabIm[MAPIM]->pos);

    traitement_input(input, &joueur1, murG, murD, gauche, droite, listeItems, ItemAffich, atlasJeu, &incrementAnim);

    affichage_barre_inv(&input,&choixAct, atlasJeu, screen);

    traitement_input_inv(&input, &joueur1, listeItems, ItemAffich, &monde, atlasJeu, screen);

    affichage_items_inv(input, atlasJeu, screen);

    affichage_crack(&monde, &incAnim, atlasJeu, minaX,minaY, &joueur1, screen);

    minage(&input,&joueur1, minaY, minaX, &incAnim, &monde);

    terreRonde(&joueur1, &murD, &murG);

    collision(&joueur1, monde.affichage, monde.posB, monde.posBY, &murD, &murG, &yMomTomb, &fait, &faitCalc, &yMomTombDeb, &touche);

    calc_vie_tombe(&joueur1, &yMomTombDeb, &faitCalc, &touche);

    game_over(&joueur1,monde, screen, &inc);

    affichage_personnage(&joueur1, atlasJeu, screen, invin);

    affichage_vie_personnage(&joueur1, atlasJeu, screen);

	  gravite_monstre(&monstre, monde);
	  affichage_monstre(&monstre, atlasJeu, screen, joueur1);
    pseudo_IA_monstre(&monstre, joueur1);
	  combat(&monstre, &joueur1, monde, &invin);

    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }


  //Sauvegarde de la map
  sauvegarde(&monde);

  //désallocation du pseudo du joueur:
  free(joueur1.nom);
  free(monstre.nom);

  detruire_monde(&monde);
  detruire_atlas(atlasJeu);
  suppression(listeItems);

  TTF_Quit();

  SDL_Quit();

  return 0;
}
