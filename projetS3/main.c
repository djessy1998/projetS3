#include <SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include "perlin.h"
#include "fonction.h"
#include "fonctions_fichiers.h"
#include "creator.h"
#include "init.h"
#include "constant.h"
#include <time.h>

void HandleEvent(SDL_Event event, input *i, character *a, monde *monde,int *incAnim, int *choixAct){
  fonction_Handle_Event(event, i, a, monde,incAnim, choixAct);
}

int main(int argc,char* argv[]){
  srand(time(NULL));
  input input;
  monde monde;
  character joueur1;
  monstre tabMo[NBMONSTRE];
  int i;
  //modifie la façon de créer le terrain
  //(plus la valeur est haute, plus le terrain est peuplé de montagnes)
  //(Une valeur au dessus de 15 créé trop de montagnes)
  int freq = 3;

  SDL_Surface *screen = initialisation_SDL();

  /*Musique de fond*/
  Mix_Music *MusicMenu = NULL;
  musiqueFond(&MusicMenu);

  /*Création de textures*/
  atlas* atlasJeu = init_atlas();

  initialisation_Jeu(&monde, &joueur1, &input, tabMo, freq, atlasJeu, argv[1]);

  int incrementAnim = 0;
  int touche = 0, incAnim = 0;
  int ItemAffich = 0, droite = 0, gauche = 0, choixAct;
  int yMomTomb = 0, fait = 0, faitCalc = 0, yMomTombDeb = 0;
  int inc = 0, nbR = rand()%(5-1) + 1;
  int booNu = 0;
  int choix[4];
  for(int i = 0; i<4; i++){
    choix[i] = 0;
  }
  double posXNu = 0;

  Liste *listeItems = initialisation();

  ItemMonde(monde,listeItems);

  while(!input.data.quit){

    compteur_fps();

    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      HandleEvent(event, &input, &joueur1, &monde, &incAnim, &choixAct);
    }

    minage(&input,&joueur1, &incAnim, &monde);

    terreRonde(&joueur1);

    collision(&joueur1, monde, &yMomTomb, &fait, &faitCalc, &yMomTombDeb, &touche);

    calc_vie_tombe(&joueur1, &yMomTombDeb, &faitCalc, &touche);

    for(i=0;i<NBMONSTRE;i++){
      if(tabMo[i].mort == 0){
        gravite_monstre(&tabMo[i], monde);
        pseudo_IA_monstre(&tabMo[i], joueur1);
        combat(&tabMo[i], &joueur1, monde, &input);
      }
    }

    //affichage
    affichage_fond(atlasJeu, screen);

    affichage_nuage(atlasJeu,screen, choix, &posXNu, &nbR, &booNu);

    affichage_monde(monde, joueur1, atlasJeu, screen);

    traitement_input_inv(&input, &joueur1, listeItems, ItemAffich, &monde, atlasJeu, screen);

    affichage_barre_inv(&input,&choixAct, atlasJeu, screen);

    affichage_items_inv(input, atlasJeu, screen);

    affichage_crack(&monde, &incAnim, atlasJeu, &joueur1, screen);

    for(i=0;i<NBMONSTRE;i++){
      if(tabMo[i].mort == 0){
        affichage_vie_monstre(&tabMo[i],atlasJeu, screen, &joueur1);
        affichage_monstre(&tabMo[i], atlasJeu, screen, joueur1);
      }
    }

    affichage_personnage(&joueur1, atlasJeu, screen);

    affichage_vie_personnage(&joueur1, atlasJeu, screen);

    affichage_mini_map(&monde, &joueur1, atlasJeu, screen);

    traitement_input(input, &joueur1, gauche, droite, listeItems, ItemAffich, atlasJeu, &incrementAnim);

    game_over(&joueur1,monde, screen, &inc, &input);

    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }


  //Sauvegarde de la map
  sauvegarde(&monde);

  detruire_Jeu(&monde, atlasJeu, joueur1, listeItems, tabMo, MusicMenu);

  return 0;
}
