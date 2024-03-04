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
  struct Array* vi = malloc(sizeof(struct Array)+_typeSize*size);
  if (!vi) {
    return NULL;
  }

  vi->typeSize = _typeSize;
  vi->len = 0;
  vi->maxLen = size;
  return (void*)vi+sizeof(struct Array);
}

void DestroyArray(void* vec){
  assert(vec != NULL);
  free(vec-sizeof(struct Array));
}

void ArrayPush(void* vec, void* data){
  assert(vec != NULL);
  assert(data != NULL);

  struct Array* state = vec-sizeof(struct Array);
  void* end = (void*)((uint64_t)vec + state->len*state->typeSize);
  if(++state->len > state->maxLen){
    state->maxLen *= 2;
    state = realloc(state, state->maxLen*state->typeSize + sizeof(struct Array));
  }
  memcpy(end, data, state->typeSize);
}

void ArrayPushBulk(void* arr, void* data, size_t size){
  assert(arr);
  assert(data);
  struct Array* state = arr-sizeof(struct Array);

  void* end = (void*)((uint64_t)arr + state->len*state->typeSize);
  state->len+=size;
  if(state->len > state->maxLen){
    state->maxLen = state->len*2;
    state = realloc(state, state->maxLen*state->typeSize + sizeof(struct Array));
  }
  memcpy(end, data, size*state->typeSize);
}

void ArrayRemove(void* vec, size_t index){
  assert(vec != NULL);
  struct Array* state = vec-sizeof(struct Array);
  assert(index < state->len);

  //Get the pointer right after the thing we want to remove
  void* startCpy = (void*)(((uint64_t)vec + index*state->typeSize)+state->typeSize);
  //Get the copy length
  uint64_t lenCpy = ((uint64_t)vec+state->len*state->typeSize) - (uint64_t)startCpy;

  memcpy((void*)((uint64_t)startCpy-state->typeSize), startCpy, lenCpy);
  state->len--;
}

void* FilterArray(void* vec, ArrayMatch_fn condition, ...){
  assert(vec != NULL);
  struct Array* state = vec-sizeof(struct Array);
  void* filtered = malloc(state->len*state->typeSize);
  if (!filtered) {
    return NULL;
  }
  void* cursor = filtered;
  va_list args;
  va_start(args, condition);

  for (size_t i = 0; i < state->len; i++) {
    const void* element = vec+i*state->typeSize;
    if(condition(element, args)){
      cursor = mempcpy(cursor, element, state->typeSize);
    }
  }
  va_end(args);
  return filtered;
}

size_t GetArrayLen(void* vec){
  assert(vec != NULL);
  struct Array* state = vec-sizeof(struct Array);
  return state->len;
}
