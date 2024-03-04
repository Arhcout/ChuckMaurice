#pragma once
#include "Error.h"
#include "Vec.h"
#include "Array.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

enum CM_ResourceType{
  CM_RESOURCE_SOUND,
  CM_RESOURCE_IMAGE,
};

struct CM_Resource{
  int type;
  void* metaData;
  void* data;
};

struct CM_AudioMeta{
  int channel;
  bool isPlaying;
};

struct CM_ImageMeta{
  struct CM_Veci2 dim;
};

/*
 * Audio: data -> Mix_Chunck*
 *        metadata -> exist
 * Image: data -> SDL_Texture*
 *        metadata -> exist
 */
enum CM_Error CM_InitResource();
void CM_CleanResource();
void CM_DestroyResource();
enum CM_Error CM_LoadResource(char* path, struct CM_Resource**  out_data);
struct CM_Resource** CM_GetResources();
