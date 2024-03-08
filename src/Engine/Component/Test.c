#include "Test.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

enum Error UpdateTestCmp(void* self, double deltaTime){
  struct TestComponent* this = self;
  //LOG("From testCmp: value %d dt: %f\n", this->value, deltaTime);
  return OK;
}

void DestroyTestCmp(void* self){
  (void)self;
  return;
}

enum Error InitTestCmp(struct TestComponent** out, int value){
  *out = malloc(sizeof(struct TestComponent));
  if(!*out){
    MALLOC_ERROR;
    return BAD;
  }

  (*out)->value = value;
  (*out)->update = UpdateTestCmp;
  (*out)->destroy = DestroyTestCmp;
  
  return OK;
}

