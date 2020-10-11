#include "graphics.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "physics/rectangle.h"
#include "texture.h"
#include "window.h"
#include "shader.h"

void graphics::_buffers_cleanup()
{
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ubo);
}

void graphics::_buffers_initialize(short* vertices, float* uvs)
{
	_buffers_cleanup();

	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ubo);
	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(short) * 12, vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, 2 * sizeof(short), 0);

	glBindBuffer(GL_ARRAY_BUFFER, _ubo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, uvs, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 2 * sizeof(float), 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void graphics::_get_vertices(short* arr, struct rectangle bounds)
{
	// bottom right
	arr[0] = bounds.x + bounds.width;
	arr[1] = bounds.y;

	// top right
	arr[2] = bounds.x + bounds.width;
	arr[3] = bounds.y + bounds.height;

	// bottom left
	arr[4] = bounds.x;
	arr[5] = bounds.y;

	// top right
	arr[6] = bounds.x + bounds.width;
	arr[7] = bounds.y + bounds.height;

	// top left
	arr[8] = bounds.x;
	arr[9] = bounds.y + bounds.height;

	// bottom left
	arr[10] = bounds.x;
	arr[11] = bounds.y;
}

void graphics::_get_UVs(float* arr, float x, float y, float width, float height)
{
	// bottom right
	arr[0] = x + width;
	arr[1] = y;

	// top right
	arr[2] = x + width;
	arr[3] = y + height;

	// bottom left
	arr[4] = x;
	arr[5] = y;

	// top right
	arr[6] = x + width;
	arr[7] = y + height;

	// top left
	arr[8] = x;
	arr[9] = y + height;

	// bottom left
	arr[10] = x;
	arr[11] = y;
}

graphics::graphics()
{

}

graphics::~graphics()
{
	_buffers_cleanup();
}

void graphics::clear(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void graphics::set_render_target(unsigned int framebuffer, unsigned int width, unsigned int height)
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glViewport(0, 0, width, height);
}

void graphics::draw(struct texture texture, struct rectangle destination, struct rectangle source, int flipped)
{
	short vertices[12];
	float uvs[12];
	_get_vertices(vertices, destination);

	if (flipped)
		_get_UVs(uvs, (source.x + source.width) / (float)texture.width, source.y / (float)texture.height, -source.width / (float)texture.width, source.height / (float)texture.height);
	else
		_get_UVs(uvs, source.x / (float)texture.width, source.y / (float)texture.height, source.width / (float)texture.width, source.height / (float)texture.height);

	_buffers_initialize(vertices, uvs);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.texture);
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void graphics::render()
{
	glfwSwapBuffers(get_window());
}