#pragma once

void shader_uniform(const char* key, int value);
void shader_use();
void shader_delete();
void shader_load(const char* vertex, const char* fragment);