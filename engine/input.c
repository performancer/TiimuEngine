#include "input.h"
#include <string.h>
#define BUFFER_SIZE 350

int _buffer[BUFFER_SIZE];
int _history[BUFFER_SIZE];

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