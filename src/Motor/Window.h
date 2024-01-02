#pragma once
#include <SDL2/SDL.h>
#include "Error.h"

typedef enum CM_Resolution_e{
  CM_RESOLUTION_1080p = 1080,
  CM_RESOLUTION_1440p = 1440
}CM_Resolution;

CM_Error CM_Window_Init(CM_Resolution res);
void CM_Window_Destroy();
CM_Error CM_Window_GetWindow(SDL_Window** out);
CM_Error CM_Window_GetRenderer(SDL_Renderer** out);
void CM_Window_Update();

