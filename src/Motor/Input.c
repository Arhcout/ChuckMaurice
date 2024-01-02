#include "Input.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool _keys[322];

void CM_Input_Init(){
  memset(_keys, false, 322*sizeof(bool));
}

CM_Error CM_Input_Poll(SDL_Event* event){
  if(event == NULL){
    fprintf(stderr, "%s:%s:%d: event Can't be null!\n",__FILE__,__func__,__LINE__);
    return CM_BAD;
  }
  switch (event->type) {
    case SDL_KEYDOWN:
      _keys[event->key.keysym.sym % 322] = true;
      break;

    case SDL_KEYUP:
      _keys[event->key.keysym.sym % 322] = false;
      break;
  }
  return CM_OK;
}

bool CM_Input_IsKeyDown(SDL_KeyCode key){
  return _keys[key];
}

void CM_Input_GetMousePosition(int* out_x, int* out_y){
  SDL_GetMouseState(out_x, out_y);
}

bool CM_Input_GetButtonState(CM_Input_MouseButtons button){
  return SDL_GetMouseState(NULL, NULL) == SDL_BUTTON(button);
}

