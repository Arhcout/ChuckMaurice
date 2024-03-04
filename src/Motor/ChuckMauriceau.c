#include "ChuckMauriceau.h"
#include "Audio.h"
#include "Entity.h"
#include "Error.h"
#include "Input.h"
#include "Player.h"
#include "Renderer.h"
#include "Ressource.h"
#include "Window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum CM_Error CM_Init(){
  if(SDL_Init(SDL_INIT_EVERYTHING) > 0){
    CM_ERROR("Can't initialize SDL2!");
    return CM_BAD;
  }

  if(CM_InitWindow(CM_RESOLUTION_1080p) == CM_BAD){
    CM_ERROR("Can't initialize window");
    return CM_BAD;
  }

  if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)){
    CM_ERROR("Can't initialize SDL_image");
    return CM_BAD;
  }
  
  CM_InputInit();

  if(CM_InitAudio() == CM_BAD){
    CM_ERROR("Can't initialize audio");
    return CM_BAD;
  }

  if(CM_InitResource() == CM_BAD){
    CM_ERROR("Can't initialize resource system");
    return CM_BAD;
  }

  if(CM_InitEntities() == CM_BAD){
    CM_ERROR("Can't init Entities");
    return CM_BAD;
  }

  return CM_OK;
}

enum CM_Error CM_Run(){
  struct CM_Resource* sound = NULL;
  if(CM_LoadResource("amongus.waw", &sound) == CM_BAD) return CM_BAD;
  
  struct CM_Resource* bg = NULL;
  if(CM_LoadResource("bg.jpg", &bg) == CM_BAD) return CM_BAD;
  CM_SetBackground(bg);

  struct CM_Resource* player = NULL;
  if(CM_LoadResource("player.png", &player) == CM_BAD) return CM_BAD;
  CM_InitPlayer(player);

  double deltaTime = 0;
  bool running = true;
  SDL_Event e;
  while (running){
    clock_t deltaStart = clock();
    while (SDL_PollEvent(&e)){
      CM_InputPoll(&e);
      switch (e.type) {
        case SDL_QUIT:
          running = false;
          break;
      }
    }

    if(CM_IsKeyDown(SDLK_e) && !CM_IsPlayingAudio(sound)){
      CM_PlayAudio(sound, 50, false);
    }

    CM_PlayerUpdate(deltaTime);

    CM_UpdateEntities(deltaTime);

    CM_Render();
    deltaTime = (double)(clock() - deltaStart) / CLOCKS_PER_SEC;
  }
  return CM_OK;
}

void CM_Quit(){
  CM_DestroyResource();
  CM_DestroyWindow();
  CM_DestroyAudio();
  IMG_Quit();
  SDL_Quit();
}
