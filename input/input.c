#include "input.h"

int _buffer[350];

void input_register(int key, int action) {
	_buffer[key] = action;
}

int input_key(int key) {
	return _buffer[key];
}