#pragma once
#include "Error.h"
#include "Ressource.h"
#include "Vec.h"

enum Error InitPlayer(struct Resource* spriteSheet);
void PlayerUpdate(double deltaTime);
const struct Vecd2* GetPlayerPos();
const struct Vecd2* GetPlayerScale();
const struct Resource* GetPlayerSprite();
