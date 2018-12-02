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

  creer_joueur(&joueur1);
  creer_monde(&monde);
  creer_input(&input);

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
  atlas* atlasJeu = init_atlas();

  //Si on ajoute un argument on "affiche" l'aléatoire du terrain avec Perlin
  if(argv[1] != NULL){
    if(atoi(argv[1]) !=0){
      gen_monde(&monde, atoi(argv[1]));
      apparition_joueur(&joueur1, monde);
      creer_monstre(&monstre, atlasJeu, monde);
    }
  }

  SDL_Surface *miniMap = creer_minimap(&monde);

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

  Liste *listeItems = initialisation();

  ItemMonde(monde,listeItems);

  int sautmonstre = 0;
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

    SDL_BlitSurface(atlasJeu->bg->surface, NULL, screen, &atlasJeu->bg->pos);

    affichage_monde(monde, joueur1, atlasJeu, screen);

    SDL_BlitSurface(miniMap, NULL, screen, &posMiniMap);

    SDL_BlitSurface(atlasJeu->map->surface, NULL, screen, &atlasJeu->map->pos);

    traitement_input(input, &joueur1, murG, murD, gauche, droite, listeItems, ItemAffich, atlasJeu, &incrementAnim);

    affichage_barre_inv(&input,&choixAct, atlasJeu, screen);

    traitement_input_inv(&input, &joueur1, listeItems, ItemAffich, &monde, atlasJeu, screen);

    affichage_items_inv(input, atlasJeu, screen);

    affichage_crack(&monde, &incAnim, atlasJeu, minaX,minaY, &joueur1, screen);

    minage(&input,&joueur1, minaY, minaX, &incAnim, &monde);

    terreRonde(&joueur1, &murD, &murG);

    collision(&joueur1, monde.affichage, monde.posB, monde.posBY, &murD, &murG, &yMomTomb, &fait, &faitCalc, &yMomTombDeb, &touche);

    calc_vie_tombe(&joueur1, &yMomTombDeb, &faitCalc, &touche);

    affichage_personnage(joueur1, atlasJeu, screen);

    affichage_vie_personnage(&joueur1, atlasJeu, screen);

    if(argv[1] != NULL){
    	if(atoi(argv[1]) !=0){
        gravite_monstre(&monstre, monde);
    	  affichage_monstre(&monstre, atlasJeu, screen, joueur1);
        // sautmonstre += 1;
        // if(sautmonstre == 1000){
        //   monstre.saut = 1;
        // }else{
        //   monstre.saut = 0;
        // }
    	}
    }

    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }


  SDL_FreeSurface(atlasJeu->bg->surface);
  SDL_FreeSurface(atlasJeu->terre->surface);
  SDL_FreeSurface(atlasJeu->casque->surface);
  SDL_FreeSurface(atlasJeu->armure->surface);
  SDL_FreeSurface(atlasJeu->character->surface);
  SDL_FreeSurface(atlasJeu->characterD->surface);
  SDL_FreeSurface(atlasJeu->invIm->surface);
  SDL_FreeSurface(atlasJeu->ActuelInv->surface);
  SDL_FreeSurface(atlasJeu->vieEnt->surface);
  SDL_FreeSurface(atlasJeu->miVie->surface);
  SDL_FreeSurface(atlasJeu->noVie->surface);
  SDL_FreeSurface(atlasJeu->tronc->surface);
  SDL_FreeSurface(atlasJeu->Crack->surface);
  SDL_FreeSurface(atlasJeu->abg->surface);
  SDL_FreeSurface(atlasJeu->abd->surface);

  TTF_Quit();

  SDL_Quit();

  //Sauvegarde de la map
  if(argv[1] != NULL){
    if(atoi(argv[1]) !=0){
    tab_int2char(monde.grilleInt, monde.grilleChar, TMONDE, TMONDE);
    ecrire_fichier("saves/MondeTest.txt", monde.grilleChar, TMONDE, TMONDE);
    }
  }

  desallouer_tab_2D_int(monde.grilleInt, TMONDE);
  desallouer_tab_2D_char(monde.grilleChar, TMONDE);
  desallouer_tab_2D_int(monde.posB, TMONDE);
  desallouer_tab_2D_int(monde.posBY,TMONDE);
  desallouer_tab_2D_int(monde.affichage, NBBLOCS_FENETREY);
  //désallocation du pseudo du joueur:
  free(joueur1.nom);
  free(monstre.nom);
  return 0;
}
