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
static struct CM_Entity** entities;

enum CM_Error CM_InitEntities(){
  entities = InitArray(struct CM_Entity*, NUM_ENTITY_AT_START);
  if(entities == NULL) return CM_BAD;

  // TODO: Read JSON to add all entities
  
  struct CM_Resource* sprite1;
  CM_LoadResource("entity.png", &sprite1);
  struct CM_Resource* sprite2;
  CM_LoadResource("entity2.png", &sprite2);

  // Hard coded
  {
    struct CM_Entity* entity;
    void* cmp;
    if(CM_InitEntity((struct CM_Vecd2){300, -50},(struct CM_Vecd2){10, 10}, 0, sprite1, (struct CM_Veci2){16,16}, 0, &entity)) return CM_BAD;
    if(CM_InitTestCmp((struct CM_TestComponent**)&cmp, 78)) return CM_BAD;
    ArrayPush(entity->components, &cmp);
  }
  {
    struct CM_Entity* entity;
    void* cmp;
    if(CM_InitEntity((struct CM_Vecd2){-300, 50},(struct CM_Vecd2){.5, .5}, 0, sprite2, ((struct CM_ImageMeta*)sprite2->metaData)->dim, 0, &entity)) return CM_BAD;
    if(CM_InitTestCmp((struct CM_TestComponent**)&cmp, 7)) return CM_BAD;
    ArrayPush(entity->components, &cmp);
  }

  return CM_OK;
}

enum CM_Error CM_InitEntity(struct CM_Vecd2 pos, struct CM_Vecd2 scale, int layer, struct CM_Resource* _spriteSheet,
                            struct CM_Veci2 _spritePartDim, double _frameIntervalSeconds, struct CM_Entity** out){
  assert(entities != NULL);
  struct CM_Entity* new = malloc(sizeof(struct CM_Entity));
  if(new == NULL){
    CM_MALLOC_ERROR;
    return CM_BAD;
  }
  if(out) *out = new;
  new->pos = pos;
  new->scale = scale;
  new->layer = layer;
  new->sprite = _spriteSheet;
  new->spritePartDim = _spritePartDim;
  new->frameIntervalSeconds = _frameIntervalSeconds;
  new->curFrame = 0;
  new->components = InitArray(void*, 16);

  ArrayPush(entities, &new);
  return CM_OK;
}

struct CM_Entity** CM_GetEntities(){
  return entities;
}

void CM_UpdateEntities(double deltaTime){
  for(size_t i = 0; i < GetArrayLen(entities); i++){
    for (size_t c = 0; c < GetArrayLen(entities[i]->components); c++){
      ((struct AnyComponent*)entities[i]->components[c])->update(entities[i]->components[c], deltaTime);
    }
  }
}

void CM_DestroyEntities(){
  for (size_t i = 0; i < GetArrayLen(entities); i++) {
    free(entities[i]);
  }
  DestroyArray(entities);
}

