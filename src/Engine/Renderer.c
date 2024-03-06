#include "Renderer.h"
#include "Array.h"
#include "Camera.h"
#include "Entity.h"
#include "Error.h"
#include "Player.h"
#include "Ressource.h"
#include "Window.h"
#include <SDL2/SDL_render.h>
#include <assert.h>
#include <stddef.h>

static const struct Resource* _bg;

void SetBackground(const struct Resource* bg){
  assert(bg != NULL);
  _bg = bg;
}

void Render(){
  SDL_Renderer* ren;
  enum Error res = GetRenderer(&ren);
  assert(res == OK);

  SDL_RenderClear(ren);

  // Render backgroung
  if(_bg != NULL){
    struct ImageMeta* bgMeta= _bg->metaData;
    SDL_Rect bgDRect = {.x = 0 - cameraPos.x, .y = 0 - cameraPos.y, .w = bgMeta->dim.x, .h = bgMeta->dim.y};
    SDL_RenderCopy(ren, _bg->data, NULL, &bgDRect);
  }
  
  struct Entity** entities = GetEntities();
  for(size_t i = 0; i < GetArrayLen(entities); i++){
    struct Entity* cur = entities[i];
    if(!cur->sprite) continue;
    SDL_Rect rectD = {
      .x = cur->pos.x - cameraPos.x,
      .y = cur->pos.y - cameraPos.y,
      .w = cur->spritePartDim.x * cur->scale.x,
      .h = cur->spritePartDim.y * cur->scale.y
    };
    SDL_Rect rectS = {
      .x = cur->spritePartDim.x*(cur->curFrame % cur->numFrames),
      .y = 0,
      .w = cur->spritePartDim.x,
      .h = cur->spritePartDim.y
    };
    SDL_RenderCopy(ren, cur->sprite->data, &rectS, &rectD);
  }
  
  struct ImageMeta* playerMeta = GetPlayerSprite()->metaData;

  int w,h;
  SDL_Window* win;
  GetWindow(&win);
  SDL_GetWindowSize(win, &w, &h);

  SDL_Rect playerDRect = {
    .x = GetPlayerPos()->x - cameraPos.x + (playerMeta->dim.x*GetPlayerScale()->x)/2.0 + w/2.0,
    .y = GetPlayerPos()->y - cameraPos.y + (playerMeta->dim.y*GetPlayerScale()->y)/2.0 + h/2.0,
    .w = playerMeta->dim.x * GetPlayerScale()->x,
    .h = playerMeta->dim.y * GetPlayerScale()->y
  };
  SDL_RenderCopy(ren, GetPlayerSprite()->data, NULL, &playerDRect);


  SDL_RenderPresent(ren);
}
