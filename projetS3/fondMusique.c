#include <SDL.h>
#include <SDL/SDL_mixer.h>
#include "constant.h"

void musiqueFond(Mix_Music **MusicMenu){
  *MusicMenu = Mix_LoadMUS("Musique/Fond.mp3");
  Mix_PlayMusic(*MusicMenu, 1);
  Mix_VolumeMusic(5);
}
