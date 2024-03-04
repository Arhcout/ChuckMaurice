#include "Audio.h"
#include "Error.h"
#include "Ressource.h"
#include "Array.h"
#include <SDL2/SDL_mixer.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static float _masterVolume = 1.0f;

static bool _VecMatch_AudioChannel(const void* element, va_list args){
  int channel = va_arg(args, int);
  const struct CM_Resource* elm = *(void**)element;
  return ((struct CM_AudioMeta*)elm->metaData)->channel == channel;
}

void _Callback_ChannelFinished(int channel){
  struct CM_Resource** res = CM_GetResources();
  struct CM_Resource** sound = FilterArray(res, _VecMatch_AudioChannel, channel);
  ((struct CM_AudioMeta*)(*sound)->metaData)->isPlaying = false;
  free(sound);
}

enum CM_Error CM_InitAudio(){
  if(Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) < 0){
    CM_ERROR("Can't init SDL_mixer: %s\n", Mix_GetError());
    return CM_BAD;
  }

  // open 22KHz, signed 16bit, system byte order,
  //      stereo audio, using 1024 byte chunks
  if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
    CM_ERROR("Can't open audio SDL_mixer: %s\n", Mix_GetError());
    return CM_BAD;
  }

  if(Mix_AllocateChannels(16) < 1){
    CM_ERROR("Can't Allocate audio channels SDL_mixer: %s\n", Mix_GetError());
    return CM_BAD;
  }

  Mix_ChannelFinished(_Callback_ChannelFinished);

  return CM_OK;
}

void CM_PlayAudio(struct CM_Resource* audio, int volume, bool loop){
  int channel = Mix_PlayChannel(-1, audio->data, -1 ? loop : 1);
  if (channel < 0) {
    CM_WARNING("Cant play audio SDL_mixer: %s\n", Mix_GetError());
    return;
  }
  Mix_Volume(channel, (int)(volume * _masterVolume));

  ((struct CM_AudioMeta*)audio->metaData)->channel = channel;
  ((struct CM_AudioMeta*)audio->metaData)->isPlaying = true;
}

bool CM_IsPlayingAudio(struct CM_Resource* audio){
  return ((struct CM_AudioMeta*)audio->metaData)->isPlaying;
}

void CM_SetMasterVolume(float volume){
  if(volume < 0.0f) volume = 0.0f;
  else if(volume > 2.0f) volume = 2.0f;
  
  _masterVolume = volume;
}

void CM_DestroyAudio(){
  Mix_CloseAudio();
  Mix_Quit();
}
