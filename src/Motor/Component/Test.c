#include "Test.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

enum CM_Error UpdateTestCmp(void* self, double deltaTime){
  struct CM_TestComponent* this = self;
  CM_LOG("From testCmp: value %d dt: %f\n", this->value, deltaTime);
  return CM_OK;
}

void DestroyTestCmp(void* self){
  (void)self;
  return;
}

enum CM_Error CM_InitTestCmp(struct CM_TestComponent** out, int value){
  *out = malloc(sizeof(struct CM_TestComponent));
  if(!*out){
    CM_MALLOC_ERROR;
    return CM_BAD;
  }

  (*out)->value = value;
  (*out)->update = UpdateTestCmp;
  (*out)->destroy = DestroyTestCmp;
  
  return CM_OK;
}

