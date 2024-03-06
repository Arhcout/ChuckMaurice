#include "Entity.h"
#include "Array.h"
#include "Component/Test.h"
#include "Error.h"
#include "Ressource.h"
#include "Vec.h"
#include "Array.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_ENTITY_AT_START 16

struct AnyComponent{
  fnUpdateComponent update;
  fnDestroyComponent destroy;
};

// If lag add multithreading
static struct Entity** entities;

enum Error InitEntities(){
  entities = InitArray(struct Entity*, NUM_ENTITY_AT_START);
  if(entities == NULL) return BAD;

  // TODO: Read JSON to add all entities
  
  struct Resource* sprite1;
  LoadResource("entity.png", &sprite1);
  struct Resource* sprite2;
  LoadResource("entity2.png", &sprite2);

  // Hard coded
  {
    struct Entity* entity;
    void* cmp;
    if(InitEntity((struct Vecd2){300, -50},(struct Vecd2){10, 10}, 1, sprite1, (struct Veci2){16,16}, 4, .5, &entity)) return BAD;
    if(InitTestCmp((struct TestComponent**)&cmp, 78)) return BAD;
    ArrayPush(entity->components, &cmp);
  }
  {
    struct Entity* entity;
    void* cmp;
    if(InitEntity((struct Vecd2){-300, 50},(struct Vecd2){.5, .5}, -1, sprite2, ((struct ImageMeta*)sprite2->metaData)->dim, 1, -1, &entity)) return BAD;
    if(InitTestCmp((struct TestComponent**)&cmp, 7)) return BAD;
    ArrayPush(entity->components, &cmp);
  }

  return OK;
}

enum Error InitEntity(struct Vecd2 pos, struct Vecd2 scale, int layer, struct Resource* _spriteSheet,
                            struct Veci2 _spritePartDim, int _frameNum, double _frameIntervalSeconds, struct Entity** out){
  assert(entities != NULL);
  struct Entity* new = malloc(sizeof(struct Entity));
  if(new == NULL){
    MALLOC_ERROR;
    return BAD;
  }
  if(out) *out = new;
  new->pos = pos;
  new->scale = scale;
  new->layer = layer;
  new->sprite = _spriteSheet;
  new->spritePartDim = _spritePartDim;
  new->frameIntervalSec = _frameIntervalSeconds;
  new->curFrame = 0;
  new->numFrames = _frameNum;
  new->components = InitArray(void*, 16);

  ArrayPush(entities, &new);
  return OK;
}

struct Entity** GetEntities(){
  return entities;
}

void UpdateEntities(double deltaTime){
  for(size_t i = 0; i < GetArrayLen(entities); i++){
    for (size_t c = 0; c < GetArrayLen(entities[i]->components); c++){
      ((struct AnyComponent*)entities[i]->components[c])->update(entities[i]->components[c], deltaTime);
    }
    if(entities[i]->frameIntervalSec == -1) continue;

    entities[i]->curFrameIntervalSec += deltaTime;
    if(entities[i]->curFrameIntervalSec > entities[i]->frameIntervalSec){
      entities[i]->curFrame++;
      entities[i]->curFrameIntervalSec = 0;
    }
  }
}

void DestroyEntities(){
  for (size_t i = 0; i < GetArrayLen(entities); i++) {
    free(entities[i]);
  }
  DestroyArray(entities);
}

