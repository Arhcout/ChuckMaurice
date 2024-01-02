#include "Vector.h"
#include "Error.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

CM_VectorInfo* CM_Vector_Init(size_t _typeSize){
    CM_VectorInfo* vi = malloc(sizeof(CM_VectorInfo));
    if (!vi) {
        CM_MALLOC_ERROR;
        return NULL;
    }

    vi->data = malloc(_typeSize);
    if (!vi->data) {
        CM_MALLOC_ERROR;
        return NULL;
    }

    vi->typeSize = _typeSize;
    vi->len = 0;
    vi->maxLen =  1;
    return vi;
}

void CM_Vector_Destroy(CM_VectorInfo* state){
    if(!state) return;
    if(state->data) free(state->data);
    free(state);
}

void CM_Vector_Push(CM_VectorInfo* state, void* data){
    if(!state) return;
    if(!data) return;
    if(++state->len > state->maxLen){
        state->maxLen *= 2;
        state->data = realloc(state->data, state->maxLen*state->typeSize);
    }
    void* end = (void*)((uint64_t)state->data+(state->len-1)*state->typeSize);
    memcpy(end, data, state->typeSize);
}

void CM_Vector_Remove(CM_VectorInfo* state, int index){
    if(!state) return;
    //Get the pointer right after the thing we want to remove
    void* startCpy = (void*)(((uint64_t)state->data+index*state->typeSize)+state->typeSize);
    //Get the copy length
    uint64_t lenCpy = ((uint64_t)state->data+state->len*state->typeSize) - (uint64_t)startCpy;
    
    memcpy((void*)((uint64_t)startCpy-state->typeSize), startCpy, lenCpy);
    state->len--;
}

void* CM_Vector_Filter(CM_VectorInfo* state, CM_Vector_Match_fn condition, ...){
    if(!state) return NULL;
    void* filtered = malloc(state->len*state->typeSize);
    if (!filtered) {
        CM_MALLOC_ERROR;
        return NULL;
    }
    void* cursor = filtered;
    va_list args;
    va_start(args, condition);

    for (size_t i = 0; i < state->len; i++) {
        const void* element = state->data+i*state->typeSize;
        if(condition(element, args)){
            cursor = mempcpy(cursor, element, state->typeSize);
        }
    }
    va_end(args);
    return filtered;
}
