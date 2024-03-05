#include "Player.h"
#include "Camera.h"
#include "Error.h"
#include "Input.h"
#include "Ressource.h"
#include "Vec.h"
#include "Window.h"
#include <SDL2/SDL_video.h>

struct Player{
  struct Vecd2 position;
  struct Vecd2 scale;
  struct Resource* sprite;
  int layer;
};
static struct Player _player;

enum Error InitPlayer(struct Resource* spriteSheet){
  _player.sprite = spriteSheet;
  _player.scale.x = 10;
  _player.scale.y = 10;
  return OK;
}

void PlayerUpdate(double deltaTime){
  if(IsKeyDown(SDLK_z)) _player.position.y -= 500.0 * deltaTime;
  if(IsKeyDown(SDLK_q)) _player.position.x -= 500.0 * deltaTime;
  if(IsKeyDown(SDLK_s)) _player.position.y += 500.0 * deltaTime;
  if(IsKeyDown(SDLK_d)) _player.position.x += 500.0 * deltaTime;
  cameraPos.x = _player.position.x;
  cameraPos.y = _player.position.y;
}

const struct Vecd2* GetPlayerPos(){
  return &_player.position;
}

const struct Vecd2* GetPlayerScale(){
  return &_player.scale;
}

const struct Resource* GetPlayerSprite(){
  return _player.sprite;
}
