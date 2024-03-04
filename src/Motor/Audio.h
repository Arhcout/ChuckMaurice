#pragma once
#include "Error.h"
#include "Ressource.h"
#include <stdbool.h>

enum CM_Error CM_InitAudio();
void CM_DestroyAudio();
void CM_PlayAudio(struct CM_Resource* audio, int volume, bool loop);
bool CM_IsPlayingAudio(struct CM_Resource* audio);
void CM_SetMasterVolume(float volume);
