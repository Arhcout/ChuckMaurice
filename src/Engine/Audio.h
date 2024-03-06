#pragma once
#include "Error.h"
#include "Ressource.h"
#include <stdbool.h>

enum Error InitAudio();
void DestroyAudio();
void PlayAudio(struct Resource* audio, int volume, bool loop);
bool IsPlayingAudio(struct Resource* audio);
void SetMasterVolume(float volume);
