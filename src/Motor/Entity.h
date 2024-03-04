#pragma once

#include "Error.h"
#include "Ressource.h"

typedef enum CM_Error (*fnUpdateComponent)(void* self, double deltaTime);
typedef void (*fnDestroyComponent)(void* self);

struct CM_Entity{
  struct CM_Vecd2 pos;
  struct CM_Vecd2 scale;
  int layer;
  struct CM_Resource* sprite;
  struct CM_Veci2 spritePartDim;
  double frameIntervalSeconds;
  int curFrame;
  void** components;
};

enum CM_Component{
  CM_TEST_COMPONENT
};

enum CM_Error CM_InitEntities(); // TODO: add JSON representation of entities
enum CM_Error CM_InitEntity(struct CM_Vecd2 pos, struct CM_Vecd2 scale, int layer, struct CM_Resource* _spriteSheet,
                            struct CM_Veci2 _spritePartDim, double _frameIntervalSeconds, struct CM_Entity** out);
void CM_UpdateEntities(double deltaTime);
void CM_DestroyEntities();

struct CM_Entity** CM_GetEntities();
