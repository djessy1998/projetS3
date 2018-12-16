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

  //Liste des objets dans le monde.
  Liste *listeItems = initialisation();

  ItemMonde(monde,listeItems);

  while(!input.data.quit){

    //Permet de limiter les images par seconde pour ne pas consommer toutes les ressources de l'ordinateur
    compteur_fps();

    //Capture les touches appuyées
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      HandleEvent(event, &input, &joueur1, &monde, &incAnim, &choixAct);
    }

    //Calcule la ou la souris clique sur l'écran si le joueur est en train de miner ou non
    minage(&input,&joueur1, &incAnim, &monde);

    //Titre aguicheur, ce sont les limites du monde, le joueur ne peut pas aller plus loin que la limite imposée
    terreRonde(&joueur1);

    //Collision avec le monde extérieur, les blocs etc..
    collision(&joueur1, monde, &yMomTomb, &fait, &faitCalc, &yMomTombDeb, &touche);

    //Si le joueur tombe de haut, il pert les points de vie en conséquence
    calc_vie_tombe(&joueur1, &yMomTombDeb, &faitCalc, &touche);

    //Parcours le tableau des monstres
    for(i=0;i<NBMONSTRE;i++){
      if(tabMo[i].mort == 0){
        //applique la gravité au monstre (et si il saute)
        gravite_monstre(&tabMo[i], monde);
        //Applique l'intelligence Artificielle  qui batterais Marcus Carlsen dans le jeu
        pseudo_IA_monstre(&tabMo[i], joueur1);
        //Systeme de combat au point
        combat(&tabMo[i], &joueur1, monde, &input);
      }
    }

    //Affichage
    //Background
    affichage_fond(atlasJeu, screen);

    affichage_nuage(atlasJeu,screen, choix, &posXNu, &nbR, &booNu);

    affichage_monde(monde, joueur1, atlasJeu, screen);

    //Affichage de l'inventaire si la touche E est appuyée
    traitement_input_inv(&input, &joueur1, listeItems, ItemAffich, &monde, atlasJeu, screen);

    //Affichage de la barre de l'inventaire
    affichage_barre_inv(&input,&choixAct, atlasJeu, screen);

    affichage_items_inv(input, atlasJeu, screen);

    //Quand on mine on voit le bloc se fissurer c'est beau.
    affichage_crack(&monde, &incAnim, atlasJeu, &joueur1, screen);

    //Parcours le tableau des monstres
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

    //Si le joueur meurt
    game_over(&joueur1,monde, screen, &inc, &input);

    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }


  //Sauvegarde de la map
  sauvegarde(&monde);

  //Libere les variables emprisonnées du monde de l'informatique
  detruire_Jeu(&monde, atlasJeu, joueur1, listeItems, tabMo, MusicMenu);

  return 0;
}
