#include "Window.h"
#include "Error.h"
#include <SDL2/SDL.h>

static SDL_Window* _win = NULL;
static SDL_Renderer* _ren = NULL;

#define _16_9_COEF 0.5625

CM_Error CM_Window_Init(CM_Resolution res){
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    CM_ERROR("Cant initialize SDL2:");
    fprintf(stderr, "%s\n", SDL_GetError());
    return CM_BAD;
  }
  
  _win = SDL_CreateWindow("ChunckMaurice prod!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, res/_16_9_COEF * 0.5, res * 0.5, SDL_WINDOW_SHOWN);
  if (_win == NULL) {
    CM_ERROR("Cant create window:");
    fprintf(stderr, "%s\n", SDL_GetError());
    return CM_BAD;
  }

  _ren = SDL_CreateRenderer(_win, -1, SDL_RENDERER_ACCELERATED);
  if (_ren == NULL) {
    CM_ERROR("Cant create renderer:");
    fprintf(stderr, "%s\n", SDL_GetError());
    return CM_BAD;
  }

  SDL_RenderSetLogicalSize(_ren, res/_16_9_COEF, res);
  return CM_OK;
}

void CM_Window_Destroy(){
  SDL_DestroyWindow(_win);
  SDL_DestroyRenderer(_ren);
}

CM_Error CM_Window_GetWindow(SDL_Window** out){
  if(_win == NULL) return CM_BAD;
  *out = _win;
  return CM_OK;
}

CM_Error CM_Window_GetRenderer(SDL_Renderer** out){
  if(_ren == NULL) return CM_BAD;
  *out = _ren;
  return CM_OK;
}

void CM_Window_Update(){
  SDL_RenderPresent(_ren);
}

