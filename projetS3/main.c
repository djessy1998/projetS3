#include <SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
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
  monstre tabMo[NBMONSTRE];
  int i;
  int freq = 1;

  creer_joueur(&joueur1);
  creer_monde(&monde);
  creer_input(&input);

  SDL_Surface *screen;
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Init(SDL_INIT_AUDIO);
  TTF_Init();

  /*Musique de fond*/
  Mix_Music *MusicMenu = NULL;
  musiqueFond(MusicMenu);

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
  for(i=0;i<NBMONSTRE;i++){
    creer_monstre(&tabMo[i], atlasJeu, monde);
  }

  int murG, murD = 0;
  int incrementAnim = 0;
  int touche = 0, incAnim = 0, minaX = 0, minaY = 0;
  int ItemAffich = 0, droite = 0, gauche = 0, choixAct;
  int yMomTomb = 0, fait = 0, faitCalc = 0, yMomTombDeb = 0;
  int actualTime = 0;
  int lastTimes = 0;
  int inc = 0, nbR = rand()%(5-1) + 1;
  int booNu = 0;
  int choix[4];
  double posXNu = 0;

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

    // printf("tabMo[0] = %d\n", tabMo[0].PV);
    // printf("tabMo[1] = %d\n", tabMo[1].PV);
    // printf("tabMo[2] = %d\n", tabMo[2].PV);
    // printf("tabMo[3] = %d\n", tabMo[3].PV);
    // printf("tabMo[4] = %d\n", tabMo[4].PV);


    minage(&input,&joueur1, minaY, minaX, &incAnim, &monde);

    terreRonde(&joueur1, &murD, &murG);

    collision(&joueur1, monde.affichage, monde.posB, monde.posBY, &murD, &murG, &yMomTomb, &fait, &faitCalc, &yMomTombDeb, &touche);

    calc_vie_tombe(&joueur1, &yMomTombDeb, &faitCalc, &touche);

    game_over(&joueur1,monde, screen, &inc);

    for(i=0;i<NBMONSTRE;i++){
      if(tabMo[i].mort == 0){
        gravite_monstre(&tabMo[i], monde);
        pseudo_IA_monstre(&tabMo[i], joueur1);
        combat(&tabMo[i], &joueur1, monde, minaX, minaY, &input);
      }
    }


    //affichage
    affichage_fond(atlasJeu, screen);

    affichage_nuage(atlasJeu,screen, choix, &posXNu, &nbR, &booNu);

    affichage_monde(monde, joueur1, atlasJeu, screen);

    affichage_barre_inv(&input,&choixAct, atlasJeu, screen);

    affichage_items_inv(input, atlasJeu, screen);

    affichage_crack(&monde, &incAnim, atlasJeu, minaX,minaY, &joueur1, screen);

    for(i=0;i<NBMONSTRE;i++){
      if(tabMo[i].mort == 0){
        affichage_vie_monstre(&tabMo[i],atlasJeu, screen, &joueur1);
        affichage_monstre(&tabMo[i], atlasJeu, screen, joueur1);
      }
    }

    affichage_personnage(&joueur1, atlasJeu, screen);

    affichage_vie_personnage(&joueur1, atlasJeu, screen);

    affichage_mini_map(&monde, &joueur1, atlasJeu, screen);

    traitement_input(input, &joueur1, murG, murD, gauche, droite, listeItems, ItemAffich, atlasJeu, &incrementAnim);

    traitement_input_inv(&input, &joueur1, listeItems, ItemAffich, &monde, atlasJeu, screen);

    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }


  //Sauvegarde de la map
  sauvegarde(&monde);

  //désallocation du pseudo du joueur:
  free(joueur1.nom);
  for(i=0;i<NBMONSTRE;i++){
    free(tabMo[i].nom);
  }

  detruire_monde(&monde);
  detruire_atlas(atlasJeu);
  suppression(listeItems);
  Mix_FreeMusic(MusicMenu);

  Mix_CloseAudio();
  TTF_Quit();
  SDL_Quit();

  return 0;
}
