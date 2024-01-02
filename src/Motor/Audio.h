#pragma once
#include "Error.h"
#include "Ressource.h"
#include <stdbool.h>

CM_Error CM_Audio_Init();
void CM_Audio_Quit();
void CM_Audio_Play(CM_Resource* audio, int volume, bool loop);
bool CM_Audio_IsPlaying(CM_Resource* audio);
void CM_Audio_SetMasterVolume(float volume);
