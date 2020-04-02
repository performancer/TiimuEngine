#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "IO/file.h"
#include "IO/image.h"
#include "shader.h"
#include "input.h"

void initialize(int width, int height, char* title);
void loadShader(char* vertex, char* fragment);

int loadTexture(char* filename);
void unloadTexture(int texture);

void run(void(*update)(float), void(*draw)());

void clear(float r, float g, float b);
void begin();
void drawSprite(unsigned int texture, short x, short y, unsigned short width, unsigned short height);
void end();