#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "input/input.h"
#include "io/file.h"
#include "io/image.h"
#include "rectangle.h"
#include "shader.h"
#include "texture.h"

#ifdef __cplusplus
extern "C" {
#endif 

	void initialize(int width, int height, const char* title);
	void loadShader(const char* vertex, const char* fragment);

	struct TEXTURE loadTexture(const char* filename);
	void unloadTexture(struct TEXTURE texture);

	void run(void(*update)(float), void(*draw)());

	void clear(float r, float g, float b);
	void begin();
	void drawSprite(struct TEXTURE texture, struct RECTANGLE destination, struct RECTANGLE source);
	void end();

#ifdef __cplusplus
}
#endif 