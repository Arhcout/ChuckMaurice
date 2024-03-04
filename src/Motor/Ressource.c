#include "Ressource.h"
#include "Window.h"
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <string.h>

static struct CM_Resource** _res;

enum CM_Error CM_InitResource(){
  _res = InitArray(struct CM_Resource*, 32);
  return CM_OK;
}

static enum CM_Error _LoadWAW(char* path, struct CM_Resource* out_data){
  out_data->data = Mix_LoadWAV(path);
  if(out_data->data == NULL){
    CM_ERROR("Can't open path: %s\n", path);
    return CM_BAD;
  }
  return CM_OK;
}

enum CM_Error CM_LoadResource(char* path, struct CM_Resource**  out_data){
  *out_data = malloc(sizeof(struct CM_Resource));
  if (!*out_data) {
    CM_MALLOC_ERROR;
    return CM_BAD;
  }
  struct CM_Resource* _out_data = *out_data;

  char* ext = path;
  while(*ext != '.') ext++;

  //!== PNG/JPG ==!
  if(strncmp(ext, ".png", 1024) == 0 || strncmp(ext, ".jpg", 1024) == 0){
    _out_data->type = CM_RESOURCE_IMAGE;
    // Geting the renderer
    SDL_Renderer* ren;
    if(CM_GetRenderer(&ren) == CM_BAD){
      CM_ERROR("Can't get renderer");
      free(_out_data);
      _out_data = NULL;
      return CM_BAD;
    }
  
    // Load the texture
    _out_data->data = IMG_LoadTexture(ren, path);
    if(_out_data->data == NULL){
      CM_ERROR("Can't load image %s: %s", path, IMG_GetError());
      free(_out_data);
      _out_data = NULL;
      return CM_BAD;
    }

    // Setup the metadata
    _out_data->metaData = malloc(sizeof(struct CM_ImageMeta));
    struct CM_ImageMeta* meta = _out_data->metaData;
    SDL_QueryTexture(_out_data->data, NULL, NULL, &meta->dim.x, &meta->dim.y);
  }
  //!== WAW ==!
  else if(strncmp(ext, ".waw", 1024) == 0){
    _out_data->type = CM_RESOURCE_SOUND;
    // load audio
    if(_LoadWAW(path, _out_data) == CM_BAD){
      free(_out_data);
      _out_data = NULL;
      return CM_BAD;
    }

    // allocate audio metadata
    _out_data->metaData = malloc(sizeof(struct CM_AudioMeta));
    // Error check
    if (!_out_data->metaData) {
      CM_MALLOC_ERROR;
      free(_out_data);
      _out_data = NULL;
      return CM_BAD;
    }
  }
  else {
    CM_WARNING("Type not implemented\n");
    return CM_WARN;
  }


  ArrayPush(_res, out_data);
  return CM_OK;
}

struct CM_Resource** CM_GetResources(){
  return _res;
}

void CM_CleanResource(){
  for(size_t i = 0; i < GetArrayLen(_res); i++){
    switch (_res[i]->type) {
      case CM_RESOURCE_SOUND:
        Mix_FreeChunk(_res[i]->data);
        free(_res[i]->metaData);
        free(_res[i]);
        break;
      
      case CM_RESOURCE_IMAGE:
        SDL_DestroyTexture(_res[i]->data);
        // free(_res[i]->metaData);
        free(_res[i]);
        
    }
    ArrayRemove(_res, i);
  }
}

void CM_DestroyResource(){
  CM_CleanResource();
  DestroyArray(_res);
}

