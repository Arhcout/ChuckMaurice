#include "Input.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static bool _keys[322];

void CM_InputInit(){
  memset(_keys, false, 322*sizeof(bool));
}

enum CM_Error CM_InputPoll(SDL_Event* event){
  assert(event != NULL);

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

bool CM_IsKeyDown(SDL_KeyCode key){
  return _keys[key];
}

void CM_GetMousePosition(struct CM_Veci2* out_mousePos){
  assert(out_mousePos != NULL);
  SDL_GetMouseState(&out_mousePos->x, &out_mousePos->y);
}

bool CM_GetButtonState(enum CM_MouseButtons button){
  return SDL_GetMouseState(NULL, NULL) == (uint32_t)SDL_BUTTON(button);
}

