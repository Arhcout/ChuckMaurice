#include "Player.h"
#include "Camera.h"
#include "Error.h"
#include "Input.h"
#include "Ressource.h"
#include "Vec.h"
#include "Window.h"
#include <SDL2/SDL_video.h>

struct Player{
  struct CM_Vecd2 position;
  struct CM_Vecd2 scale;
  struct CM_Resource* sprite;
  int layer;
};
static struct Player _player;

enum CM_Error CM_InitPlayer(struct CM_Resource* spriteSheet){
  _player.sprite = spriteSheet;
  _player.scale.x = 10;
  _player.scale.y = 10;
  return CM_OK;
}

void CM_PlayerUpdate(double deltaTime){
  if(CM_IsKeyDown(SDLK_z)) _player.position.y -= 500.0 * deltaTime;
  if(CM_IsKeyDown(SDLK_q)) _player.position.x -= 500.0 * deltaTime;
  if(CM_IsKeyDown(SDLK_s)) _player.position.y += 500.0 * deltaTime;
  if(CM_IsKeyDown(SDLK_d)) _player.position.x += 500.0 * deltaTime;
  CM_cameraPos.x = _player.position.x;
  CM_cameraPos.y = _player.position.y;
}

const struct CM_Vecd2* CM_GetPlayerPos(){
  return &_player.position;
}

const struct CM_Vecd2* CM_GetPlayerScale(){
  return &_player.scale;
}

const struct CM_Resource* CM_GetPlayerSprite(){
  return _player.sprite;
}
