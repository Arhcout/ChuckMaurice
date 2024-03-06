#include "Window.h"
#include "Error.h"
#include <SDL2/SDL.h>

static SDL_Window* _win = NULL;
static SDL_Renderer* _ren = NULL;

#define _16_9_COEF 0.5625

enum Error InitWindow(enum Resolution res){
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    ERROR("Cant initialize SDL2: %s\n", SDL_GetError());
    return BAD;
  }
  
  _win = SDL_CreateWindow("ChunckMaurice prod !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, res/_16_9_COEF * 0.5, res * 0.5, SDL_WINDOW_SHOWN);
  if (_win == NULL) {
    ERROR("Cant create window: %s\n", SDL_GetError());
    return BAD;
  }

  _ren = SDL_CreateRenderer(_win, -1, SDL_RENDERER_ACCELERATED);
  if (_ren == NULL) {
    ERROR("Cant create renderer: %s\n", SDL_GetError());
    return BAD;
  }

  SDL_RenderSetLogicalSize(_ren, res/_16_9_COEF, res);
  return OK;
}

void DestroyWindow(){
  SDL_DestroyWindow(_win);
  SDL_DestroyRenderer(_ren);
}

enum Error GetWindow(SDL_Window** out){
  if(_win == NULL) return BAD;
  *out = _win;
  return OK;
}

enum Error GetRenderer(SDL_Renderer** out){
  if(_ren == NULL) return BAD;
  *out = _ren;
  return OK;
}

void Window_Update(){
}

