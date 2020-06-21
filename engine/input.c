#include "input.h"

int _buffer[350];

void input_register(int key, int action)
{
	_buffer[key] = action;
}

int is_key_down(int key) 
{
	return _buffer[key];
}

int is_key_up(int key)
{
	return !_buffer[key];
}