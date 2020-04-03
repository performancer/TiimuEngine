#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "io/file.h"
#include "io/image.h"
#include "shader.h"
#include "input/input.h"

#ifdef __cplusplus
extern "C" {
#endif 

	void initialize(int width, int height, const char* title);
	void loadShader(const char* vertex, const char* fragment);

	int loadTexture(const char* filename);
	void unloadTexture(int texture);

	void run(void(*update)(float), void(*draw)());

	void clear(float r, float g, float b);
	void begin();
	void drawSprite(unsigned int texture, short x, short y, unsigned short width, unsigned short height);
	void end();

#ifdef __cplusplus
}
#endif 