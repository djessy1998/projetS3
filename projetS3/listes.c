#include "fonction.h"
#include <stdio.h>
#include <stdlib.h>

Liste *initialisation()
{
  Liste *liste = malloc(sizeof(*liste));
  items *EItems = malloc(sizeof(*EItems));
  if (liste == NULL || EItems == NULL)
    {
      exit(EXIT_FAILURE);
    }
  EItems->type = -1;
  EItems->iItem= -1;
  EItems->jItem = -1;
  EItems->suivant = NULL;
  liste->premier = EItems;
  return liste;
}

void insertion(Liste *liste, int nvType, int nvXMonde, int nvYMonde)
{
  items *nouveau = malloc(sizeof(*nouveau));
  if (liste == NULL || nouveau == NULL)
    {
      exit(EXIT_FAILURE);
    }
  nouveau->type = nvType;
  nouveau->iItem = nvXMonde;
  nouveau->jItem = nvYMonde;
  nouveau->suivant = liste->premier;
  liste->premier = nouveau;
}

void suppression(Liste *liste)
{
  if (liste == NULL)
    {
      exit(EXIT_FAILURE);
    }
  if (liste->premier != NULL)
    {
      items *aSupprimer = liste->premier;
      liste->premier = liste->premier->suivant;
      free(aSupprimer);
    }
}

//pour le debuguage
void afficherListe(Liste *liste)
{
  if (liste == NULL)
    {
      exit(EXIT_FAILURE);
    }
  items *actuel = liste->premier;
  while (actuel != NULL)
    {
      actuel = actuel->suivant;
    }
}

void TrierInv(int rienI, items inv[4][10], int type)
{
  int o, p = 0;
  int trouve = 0;
  if(rienI == 0)
    {
      while(trouve == 0 && o < 4)
  {
    while(trouve == 0)
            {
        if(inv[o][p].type == -1)
    {
      inv[o][p].type = type;
      trouve = 1;
    }
              p = p + 1;
            }
    o = o + 1;
  }
      o = 0;
      p = 0;
    }
}

void ItemMonde(monde monde, Liste *liste){
  int i, j;
  for(i=0;i<TMONDE;i++){
    for(j=0;j<TMONDE;j++){
      if(monde.grilleInt[i][j] == 2){
        insertion(liste, 2 ,i + 1, j + 1);
      }
      else if(monde.grilleInt[i][j] == 3){
        insertion(liste, 3, i + 1, j + 1);
      }
    }
  }
}
