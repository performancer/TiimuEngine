#include "input.h"
#include "vector.h"
#include "window.h"
#include <stdio.h>
#include <string.h>
#include <GLFW/glfw3.h>
#define buffer_size 350

int _buffer[buffer_size];
int _history[buffer_size];

void input_register(int key, int action)
{
	_buffer[key] = action;
}

void input_flush()
{
	memcpy(_history, _buffer, sizeof(_buffer));
}

int key_down(int key)
{
	return _buffer[key];
}

int key_up(int key)
{
	return !_buffer[key];
}

int key_pressed(int key)
{
	return !_history[key] && _buffer[key];
}

int key_released(int key)
{
	return _history[key] && !_buffer[key];
}

struct vector get_mouse_position()
{
	double xpos, ypos;
	glfwGetCursorPos(get_window(), &xpos, &ypos);

	return {.x = (float)xpos, .y = (float)ypos};
}