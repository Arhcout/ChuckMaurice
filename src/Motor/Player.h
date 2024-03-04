#pragma once
#include "Error.h"
#include "Ressource.h"
#include "Vec.h"

enum CM_Error CM_InitPlayer(struct CM_Resource* spriteSheet);
void CM_PlayerUpdate(double deltaTime);
const struct CM_Vecd2* CM_GetPlayerPos();
const struct CM_Vecd2* CM_GetPlayerScale();
const struct CM_Resource* CM_GetPlayerSprite();
