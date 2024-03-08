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

enum Error Init(){
  if(SDL_Init(SDL_INIT_EVERYTHING) > 0){
    ERROR("Can't initialize SDL2!");
    return BAD;
  }

  if(InitWindow(RESOLUTION_1080p) == BAD){
    ERROR("Can't initialize window");
    return BAD;
  }

  if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)){
    ERROR("Can't initialize SDL_image");
    return BAD;
  }
  
  InputInit();

  if(InitAudio() == BAD){
    ERROR("Can't initialize audio");
    return BAD;
  }

  if(InitResource() == BAD){
    ERROR("Can't initialize resource system");
    return BAD;
  }

  if(InitEntities() == BAD){
    ERROR("Can't init Entities");
    return BAD;
  }

  return OK;
}

enum Error Run(){
  struct Resource* sound = NULL;
  if(LoadResource("amongus.waw", &sound) == BAD) return BAD;
  
  struct Resource* bg = NULL;
  if(LoadResource("bg.jpg", &bg) == BAD) return BAD;
  SetBackground(bg);

  struct Resource* player = NULL;
  if(LoadResource("player.png", &player) == BAD) return BAD;
  InitPlayer(player);

  double deltaTime = 0;
  bool running = true;
  SDL_Event e;
  int countedFrames = 0;
  double timer = 0;
  while (running){
    clock_t deltaStart = clock();
    
    while (SDL_PollEvent(&e)){
      InputPoll(&e);
      switch (e.type) {
        case SDL_QUIT:
          running = false;
          break;
      }
    }

    if(IsKeyDown(SDLK_e) && !IsPlayingAudio(sound)){
      PlayAudio(sound, 50, false);
    }

    PlayerUpdate(deltaTime);

    UpdateEntities(deltaTime);

    Render();
    countedFrames++;
    timer += deltaTime;
    if(timer >= 1){
      timer = 0;
      LOG("FPS: %d\n", countedFrames);
    }
    deltaTime = (double)(clock() - deltaStart) / CLOCKS_PER_SEC;
  }
  return OK;
}

void Quit(){
  DestroyResource();
  DestroyWindow();
  DestroyAudio();
  IMG_Quit();
  SDL_Quit();
}
