#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "Error.h"

typedef enum CM_Input_MouseButtons_e{
  CM_INPUT_MOUSE_LEFT = 1,
  CM_INPUT_MOUSE_MIDDLE = 2,
  CM_INPUT_MOUSE_RIGHT = 3,
}CM_Input_MouseButtons;

void CM_Input_Init();
CM_Error CM_Input_Poll(SDL_Event* event);

bool CM_Input_IsKeyDown(SDL_KeyCode key);
void CM_Input_GetMousePosition(int* out_x, int* out_y);
bool CM_Input_GetButtonState(CM_Input_MouseButtons button);
