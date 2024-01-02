#pragma once
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

#define CM_Vector_GetVal(vec,type,index) (*(type*)(vec->data + index*vec->typeSize))

typedef bool (*CM_Vector_Match_fn)(const void* element, va_list args);

typedef struct CM_VectorInfo_s{
  size_t typeSize;
  size_t len;
  size_t maxLen;
  void* data;
}CM_VectorInfo;

CM_VectorInfo* CM_Vector_Init(size_t _typeSize);
void CM_Vector_Destroy(CM_VectorInfo* state);

void CM_Vector_Push(CM_VectorInfo* state, void* data);
void CM_Vector_Remove(CM_VectorInfo* state, int index);
void* CM_Vector_Filter(CM_VectorInfo* state, CM_Vector_Match_fn lam, ...);

