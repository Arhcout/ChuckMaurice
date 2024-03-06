#pragma once
#include "Error.h"
#include "Vec.h"
#include "Array.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

enum ResourceType{
  RESOURCE_SOUND,
  RESOURCE_IMAGE,
};

struct Resource{
  int type;
  void* metaData;
  void* data;
};

struct AudioMeta{
  int channel;
  bool isPlaying;
};

struct ImageMeta{
  struct Veci2 dim;
};

/*
 * Audio: data -> Mix_Chunck*
 *        metadata -> exist
 * Image: data -> SDL_Texture*
 *        metadata -> exist
 */
enum Error InitResource();
void CleanResource();
void DestroyResource();
enum Error LoadResource(char* path, struct Resource**  out_data);
struct Resource** GetResources();
