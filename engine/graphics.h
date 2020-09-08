#pragma once

class graphics
{
private:
	unsigned int _vao, _vbo, _ubo;
	void _buffers_cleanup();
	void _buffers_initialize(short* vertices, float* uvs);
	void _get_vertices(short* arr, struct rectangle bounds);
	void _get_UVs(float* arr, float x, float y, float width, float height);
public:
	graphics();
	~graphics();
	void clear(float r, float g, float b);
	void set_render_target(unsigned int framebuffer, unsigned int width, unsigned int height);
	void draw(struct texture texture, struct rectangle destination, struct rectangle source, int flipped);
	void render();
};