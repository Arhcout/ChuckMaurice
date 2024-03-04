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

static const struct CM_Resource* _bg;

void CM_SetBackground(const struct CM_Resource* bg){
  assert(bg != NULL);
  _bg = bg;
}

void CM_Render(){
  SDL_Renderer* ren;
  enum CM_Error res = CM_GetRenderer(&ren);
  assert(res == CM_OK);

  SDL_RenderClear(ren);

  // Render backgroung
  if(_bg != NULL){
    struct CM_ImageMeta* bgMeta= _bg->metaData;
    SDL_Rect bgDRect = {.x = 0 - CM_cameraPos.x, .y = 0 - CM_cameraPos.y, .w = bgMeta->dim.x, .h = bgMeta->dim.y};
    SDL_RenderCopy(ren, _bg->data, NULL, &bgDRect);
  }
  
  struct CM_Entity** entities = CM_GetEntities();
  for(size_t i = 0; i < GetArrayLen(entities); i++){
    struct CM_Entity* cur = entities[i];
    if(!cur->sprite) continue;
    SDL_Rect rectD = {
      .x = cur->pos.x - CM_cameraPos.x,
      .y = cur->pos.y - CM_cameraPos.y,
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
  
  struct CM_ImageMeta* playerMeta = CM_GetPlayerSprite()->metaData;

  int w,h;
  SDL_Window* win;
  CM_GetWindow(&win);
  SDL_GetWindowSize(win, &w, &h);

  SDL_Rect playerDRect = {
    .x = CM_GetPlayerPos()->x - CM_cameraPos.x + (playerMeta->dim.x*CM_GetPlayerScale()->x)/2.0 + w/2.0,
    .y = CM_GetPlayerPos()->y - CM_cameraPos.y + (playerMeta->dim.y*CM_GetPlayerScale()->y)/2.0 + h/2.0,
    .w = playerMeta->dim.x * CM_GetPlayerScale()->x,
    .h = playerMeta->dim.y * CM_GetPlayerScale()->y
  };
  SDL_RenderCopy(ren, CM_GetPlayerSprite()->data, NULL, &playerDRect);


  SDL_RenderPresent(ren);
}
