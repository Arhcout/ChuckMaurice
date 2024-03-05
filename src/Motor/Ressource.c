#include "Ressource.h"
#include "Window.h"
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <string.h>

static struct Resource** _res;

enum Error InitResource(){
  _res = InitArray(struct Resource*, 32);
  return OK;
}

static enum Error _LoadWAW(char* path, struct Resource* out_data){
  out_data->data = Mix_LoadWAV(path);
  if(out_data->data == NULL){
    ERROR("Can't open path: %s\n", path);
    return BAD;
  }
  return OK;
}

enum Error LoadResource(char* path, struct Resource**  out_data){
  *out_data = malloc(sizeof(struct Resource));
  if (!*out_data) {
    MALLOC_ERROR;
    return BAD;
  }
  struct Resource* _out_data = *out_data;

  char* ext = path;
  while(*ext != '.') ext++;

  //!== PNG/JPG ==!
  if(strncmp(ext, ".png", 1024) == 0 || strncmp(ext, ".jpg", 1024) == 0){
    _out_data->type = RESOURCE_IMAGE;
    // Geting the renderer
    SDL_Renderer* ren;
    if(GetRenderer(&ren) == BAD){
      ERROR("Can't get renderer");
      free(_out_data);
      _out_data = NULL;
      return BAD;
    }
  
    // Load the texture
    _out_data->data = IMG_LoadTexture(ren, path);
    if(_out_data->data == NULL){
      ERROR("Can't load image %s: %s", path, IMG_GetError());
      free(_out_data);
      _out_data = NULL;
      return BAD;
    }

    // Setup the metadata
    _out_data->metaData = malloc(sizeof(struct ImageMeta));
    struct ImageMeta* meta = _out_data->metaData;
    SDL_QueryTexture(_out_data->data, NULL, NULL, &meta->dim.x, &meta->dim.y);
  }
  //!== WAW ==!
  else if(strncmp(ext, ".waw", 1024) == 0){
    _out_data->type = RESOURCE_SOUND;
    // load audio
    if(_LoadWAW(path, _out_data) == BAD){
      free(_out_data);
      _out_data = NULL;
      return BAD;
    }

    // allocate audio metadata
    _out_data->metaData = malloc(sizeof(struct AudioMeta));
    // Error check
    if (!_out_data->metaData) {
      MALLOC_ERROR;
      free(_out_data);
      _out_data = NULL;
      return BAD;
    }
  }
  else {
    WARNING("Type not implemented\n");
    return WARN;
  }


  ArrayPush(_res, out_data);
  return OK;
}

struct Resource** GetResources(){
  return _res;
}

void CleanResource(){
  for(size_t i = 0; i < GetArrayLen(_res); i++){
    switch (_res[i]->type) {
      case RESOURCE_SOUND:
        Mix_FreeChunk(_res[i]->data);
        free(_res[i]->metaData);
        free(_res[i]);
        break;
      
      case RESOURCE_IMAGE:
        SDL_DestroyTexture(_res[i]->data);
        // free(_res[i]->metaData);
        free(_res[i]);
        
    }
    ArrayRemove(_res, i);
  }
}

void DestroyResource(){
  CleanResource();
  DestroyArray(_res);
}

