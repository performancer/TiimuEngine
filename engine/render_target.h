#pragma once

struct render_target
{
	unsigned int framebuffer;
	unsigned short width, height;
	unsigned int texture;
};


struct render_target render_target_create(unsigned short width, unsigned short height);