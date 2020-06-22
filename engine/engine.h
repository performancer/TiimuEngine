#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "vector.h"
#include "rectangle.h"
#include "texture.h"
#include "render_target.h"
#include "shader.h"
#include "graphics.h"

#include "input.h"
#include "keys.h"

#include "audio/audio.h"

#ifdef __cplusplus
extern "C"
{
#endif

	void engine_initialize(int width, int height, const char* title);
	void engine_run(void(*update)(float), void(*draw)(float));
	void engine_resize_viewport(int width, int height);
	struct vector engine_monitor_resolution();

#ifdef __cplusplus
}
#endif 

#endif