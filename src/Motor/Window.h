#pragma once
#include <SDL2/SDL.h>
#include "Error.h"

enum CM_Resolution{
  CM_RESOLUTION_1080p = 1080,
  CM_RESOLUTION_1440p = 1440
};

enum CM_Error CM_InitWindow(enum CM_Resolution res);
void CM_DestroyWindow();
enum CM_Error CM_GetWindow(SDL_Window** out);
enum CM_Error CM_GetRenderer(SDL_Renderer** out);
void CM_UpdateWindow();

