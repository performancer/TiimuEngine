#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "shader.h"

#ifdef __cplusplus
extern "C"
{
#endif 

	void graphics_clear(float r, float g, float b);
	void graphics_cleanup();
	void graphics_draw(struct texture texture, struct rectangle destination, struct rectangle source, int flipped);
	void graphics_set_render_target(unsigned int framebuffer, unsigned int width, unsigned int height);
	void graphics_render();

#ifdef __cplusplus
}
#endif 

#endif