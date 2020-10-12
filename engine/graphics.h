#pragma once
#include "physics/vector.h"

class graphics
{
private:
	unsigned int _vao, _vbo, _ubo;
	void _buffers_cleanup();
	void _buffers_initialize(float* vertices, float* uvs);
	void _vertices(float* arr, float x, float y, float width, float height);
public:
	graphics();
	~graphics();
	void clear(float r, float g, float b);
	void set_render_target(unsigned int framebuffer, unsigned int width, unsigned int height);
	void draw(struct texture texture, Vector destination, struct rectangle source, int flipped = false);
	void draw(struct texture texture, Vector destination, struct rectangle source, float scale, int flipped = false);
	void render();
};