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
  const struct Resource* elm = *(void**)element;
  return ((struct AudioMeta*)elm->metaData)->channel == channel;
}

void _Callback_ChannelFinished(int channel){
  struct Resource** res = GetResources();
  struct Resource** sound = FilterArray(res, _VecMatch_AudioChannel, channel);
  ((struct AudioMeta*)(*sound)->metaData)->isPlaying = false;
  free(sound);
}

enum Error InitAudio(){
  if(Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) < 0){
    ERROR("Can't init SDL_mixer: %s\n", Mix_GetError());
    return BAD;
  }

  // open 22KHz, signed 16bit, system byte order,
  //      stereo audio, using 1024 byte chunks
  if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
    ERROR("Can't open audio SDL_mixer: %s\n", Mix_GetError());
    return BAD;
  }

  if(Mix_AllocateChannels(16) < 1){
    ERROR("Can't Allocate audio channels SDL_mixer: %s\n", Mix_GetError());
    return BAD;
  }

  Mix_ChannelFinished(_Callback_ChannelFinished);

  return OK;
}

void PlayAudio(struct Resource* audio, int volume, bool loop){
  int channel = Mix_PlayChannel(-1, audio->data, -1 ? loop : 1);
  if (channel < 0) {
    WARNING("Cant play audio SDL_mixer: %s\n", Mix_GetError());
    return;
  }
  Mix_Volume(channel, (int)(volume * _masterVolume));

  ((struct AudioMeta*)audio->metaData)->channel = channel;
  ((struct AudioMeta*)audio->metaData)->isPlaying = true;
}

bool IsPlayingAudio(struct Resource* audio){
  return ((struct AudioMeta*)audio->metaData)->isPlaying;
}

void SetMasterVolume(float volume){
  if(volume < 0.0f) volume = 0.0f;
  else if(volume > 2.0f) volume = 2.0f;
  
  _masterVolume = volume;
}

void DestroyAudio(){
  Mix_CloseAudio();
  Mix_Quit();
}
