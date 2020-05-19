#ifndef _SHADER_H_
#define _SHADER_H_

void shader_set(const char* vertex, const char* fragment);
void shader_uniform(const char* key, int value);
void shader_use();
void shader_delete();

#endif