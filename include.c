#include "include.h"
#include "graphics/shader.h"
#include "input/input.h"
#include "io/file.h"

void loadShader(const char* vertex, const char* fragment) {
	char* vdata = readFile(vertex);
	char* fdata = readFile(fragment);
	shader_set(vdata, fdata);
}

void shaderParameter(const char* key, int value) {
	shader_uniform(key, value);
}

int isKeyDown(int key) {
	return input_key(key);
}

int isKeyUp(int key) {
	return !input_key(key);
}