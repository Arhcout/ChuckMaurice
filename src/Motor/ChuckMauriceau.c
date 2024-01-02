#include "ChuckMauriceau.h"
#include "Audio.h"
#include "Error.h"
#include "Input.h"
#include "Ressource.h"
#include "Window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

CM_Error CM_Init(){
  if(SDL_Init(SDL_INIT_EVERYTHING) > 0){
    CM_ERROR("Can't initialize SDL2!");
    return CM_BAD;
  }

  if(CM_Window_Init(CM_RESOLUTION_1080p) == CM_BAD){
    CM_ERROR("Can't initialize window");
    return CM_BAD;
  }
  
  CM_Input_Init();

  if(CM_Audio_Init() == CM_BAD){
    CM_ERROR("Can't initialize audio");
    return CM_BAD;
  }

  if(CM_Resource_Init() == CM_BAD){
    CM_ERROR("Can't initialize resource systeme");
    return CM_BAD;
  }

  return CM_OK;
}

CM_Error CM_Run(){
  CM_Resource* sound = NULL;
  if(CM_Resource_Load("amongus.waw", &sound) == CM_BAD) return CM_BAD;
  

  bool running = true;
  SDL_Event e;
  while (running){
    while (SDL_PollEvent(&e)){
      CM_Input_Poll(&e);
      switch (e.type) {
        case SDL_QUIT:
          running = false;
          break;
      }
    }

    if(CM_Input_IsKeyDown(SDLK_e) && !CM_Audio_IsPlaying(sound)){
      CM_Audio_Play(sound, 50, false);
    }

    CM_Window_Update();
  }
  return CM_OK;
}

void CM_Quit(){
  CM_Window_Destroy();
  CM_Audio_Quit();
  CM_Resource_Quit();
  SDL_Quit();
}
