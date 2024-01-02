#include "Ressource.h"
#include "Error.h"
#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_mixer.h>
#include <string.h>

static CM_VectorInfo* _res;

CM_Error CM_Resource_Init(){
  _res = CM_Vector_Init(sizeof(CM_Resource*));
  return CM_OK;
}

static CM_Error _LoadWAW(char* path, CM_Resource* out_data){
  out_data->data = Mix_LoadWAV(path);
  if(out_data->data == NULL){
    CM_ERROR("Can't open path:");
    fprintf(stderr, "%s\n", path);
    return CM_BAD;
  }
  return CM_OK;
}

CM_Error CM_Resource_Load(char* path, CM_Resource**  out_data){
  *out_data = malloc(sizeof(CM_Resource));
  if (!out_data) {
    CM_MALLOC_ERROR;
    return CM_BAD;
  }

  char* ext = path;
  while(*ext != '.') ext++;
  
  if(strncmp(ext, ".waw", 1024) == 0){
    (*out_data)->type = CM_RESOURCE_SOUND;
    // load audio
    if(_LoadWAW(path, *out_data) == CM_BAD){
      free(*out_data);
      *out_data = NULL;
      return CM_BAD;
    }

    // allocate audio metadata
    (*out_data)->metaData = malloc(sizeof(CM_Resource_AudioMeta));
    if (!(*out_data)->metaData) {
      CM_MALLOC_ERROR;
      free(*out_data);
      *out_data = NULL;
      return CM_BAD;
    }
  }
  else {
    CM_WARNING("Type not implemented");
    return CM_WARN;
  }


  CM_Vector_Push(_res, out_data);
  return CM_OK;
}

CM_VectorInfo* CM_Resource_GetResources(){
  return _res;
}

void CM_Resource_Clean(){
  for(size_t i = 0; i < _res->len; i++){
    CM_Resource* res = CM_Vector_GetVal(_res,CM_Resource*,i);
    switch (res->type) {
      case CM_RESOURCE_SOUND:
        Mix_FreeChunk(res->data);
        if(res->metaData) free(res->metaData);
        free(res);
        break;
    }
    CM_Vector_Remove(_res, i);
  }
}

void CM_Resource_Quit(){
  CM_Resource_Clean();
  CM_Vector_Destroy(_res);
}

