#pragma once
#include <SDL2/SDL.h>
#include "Error.h"

enum Resolution{
  RESOLUTION_1080p = 1080,
  RESOLUTION_1440p = 1440
};

enum Error InitWindow(enum Resolution res);
void DestroyWindow();
enum Error GetWindow(SDL_Window** out);
enum Error GetRenderer(SDL_Renderer** out);
void UpdateWindow();

