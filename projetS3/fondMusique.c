#include <SDL.h>
#include <SDL/SDL_mixer.h>

void musiqueFond(Mix_Music *MusicMenu){
  SDL_Init(SDL_INIT_AUDIO);
  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
  MusicMenu = NULL;
  MusicMenu = Mix_LoadMUS("Musique/Fond.mp3");
  Mix_PlayMusic(MusicMenu, 1);
  Mix_VolumeMusic(5);
}
