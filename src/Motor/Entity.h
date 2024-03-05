#pragma once

#include "Error.h"
#include "Ressource.h"

typedef enum Error (*fnUpdateComponent)(void* self, double deltaTime);
typedef void (*fnDestroyComponent)(void* self);

struct Entity{
  struct Vecd2 pos;
  struct Vecd2 scale;
  int layer;
  struct Resource* sprite;
  struct Veci2 spritePartDim;
  double frameIntervalSec;
  double curFrameIntervalSec;
  int curFrame;
  int numFrames;
  void** components;
};

enum Component{
  TEST_COMPONENT
};

enum Error InitEntities(); // TODO: add JSON representation of entities
enum Error InitEntity(struct Vecd2 pos, struct Vecd2 scale, int layer, struct Resource* _spriteSheet,
                            struct Veci2 _frameSize, int _frameNum, double _frameIntervalSeconds, struct Entity** out);
void UpdateEntities(double deltaTime);
void DestroyEntities();


struct Entity** GetEntities();
