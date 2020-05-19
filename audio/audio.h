#ifndef _AUDIO_H_
#define _AUDIO_H_

#ifdef __cplusplus
extern "C" {
#endif 

int audio_initialize();
int audio_play(const char* path);

#ifdef __cplusplus
}
#endif 

#endif