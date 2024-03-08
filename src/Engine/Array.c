#include "Array.h"
#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Array{
  size_t typeSize;
  size_t len;
  size_t maxLen;
};

void* ManualInitArray(size_t _typeSize, size_t size){
  struct Array* state = malloc(sizeof(struct Array)+_typeSize*size);
  if (!state) {
    return NULL;
  }

  state->typeSize = _typeSize;
  state->len = 0;
  state->maxLen = size;
  return (void*)state+sizeof(struct Array);
}

void DestroyArray(void* arr){
  assert(arr != NULL);
  free(arr-sizeof(struct Array));
}

void* ManualArrayPushBulk(void* arr, void* data, size_t size){
  assert(arr);
  assert(data);
  struct Array* state = arr-sizeof(struct Array);

  state->len+=size;
  if(state->len > state->maxLen){
    do state->maxLen *= 2; while (state->len > state->maxLen);
    state = realloc(state, state->maxLen*state->typeSize + sizeof(struct Array));
    arr = (void*)((uintptr_t)state + sizeof(struct Array));
  }
  void* end = (void*)((uintptr_t)arr + (state->len-size)*state->typeSize);
  memcpy(end, data, size*state->typeSize);
  return arr;
}

void ArrayRemove(void* arr, size_t index){
  assert(arr != NULL);
  struct Array* state = arr-sizeof(struct Array);
  assert(index < state->len);

  //Get the pointer right after the thing we want to remove
  void* startCpy = (void*)(((uint64_t)arr + index*state->typeSize)+state->typeSize);
  //Get the copy length
  uint64_t lenCpy = ((uint64_t)arr+state->len*state->typeSize) - (uint64_t)startCpy;

  memcpy((void*)((uint64_t)startCpy-state->typeSize), startCpy, lenCpy);
  state->len--;
}

void* CopyArray(void* arr){
  assert(arr);
  struct Array* state = arr-sizeof(struct Array);
  struct Array* new = malloc(sizeof(struct Array)+state->typeSize*state->len);
  memcpy(new, state, sizeof(struct Array)+state->typeSize*state->len);
  return (void*)((uintptr_t)new+sizeof(struct Array));
}

size_t GetArrayLen(void* arr){
  assert(arr != NULL);
  struct Array* state = arr-sizeof(struct Array);
  return state->len;
}
