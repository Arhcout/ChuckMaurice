#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "Error.h"
#include "Vec.h"

enum CM_MouseButtons{
  CM_INPUT_MOUSE_LEFT = 1,
  CM_INPUT_MOUSE_MIDDLE = 2,
  CM_INPUT_MOUSE_RIGHT = 3,
};

void CM_InputInit();
enum CM_Error CM_InputPoll(SDL_Event* event);

bool CM_IsKeyDown(SDL_KeyCode key);
void CM_GetMousePosition(struct CM_Veci2* mousePos);
bool CM_GetButtonState(enum CM_MouseButtons button);
