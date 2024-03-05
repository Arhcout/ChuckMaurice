#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "Error.h"
#include "Vec.h"

enum MouseButtons{
  INPUT_MOUSE_LEFT = 1,
  INPUT_MOUSE_MIDDLE = 2,
  INPUT_MOUSE_RIGHT = 3,
};

void InputInit();
enum Error InputPoll(SDL_Event* event);

bool IsKeyDown(SDL_KeyCode key);
void GetMousePosition(struct Veci2* mousePos);
bool GetButtonState(enum MouseButtons button);
