#pragma once
#include "Error.h"
#include "Vector.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum CM_Resource_Type_e{
  CM_RESOURCE_SOUND,
  CM_RESOURCE_IMAGE,
}CM_Resource_Type;

typedef struct CM_Resource_s{
  int type;
  void* metaData;
  void* data;
}CM_Resource;

typedef struct CM_Resource_AudioMeta_s{
  int channel;
  bool isPlaying;
}CM_Resource_AudioMeta;

CM_Error CM_Resource_Init();
void CM_Resource_Clean();
void CM_Resource_Quit();
CM_Error CM_Resource_Load(char* path, CM_Resource**  out_data);
CM_VectorInfo* CM_Resource_GetResources();
