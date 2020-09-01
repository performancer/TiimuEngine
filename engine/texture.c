#include "texture.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "io/image.h"
#include <stdlib.h>
#include <stdio.h>

struct texture texture_load(const char* path)
{
	unsigned int texture_handle;
	glGenTextures(1, &texture_handle);
	glBindTexture(GL_TEXTURE_2D, texture_handle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unsigned int width, height;
	unsigned char* image = loadImage(path, &width, &height);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, image);

	if (image == 0)
	{
		printf("ERROR::TEXTURE::LOADING_FAILED\n%s\n", path);
		exit(1);
	}

	free(image);

	struct texture t = { texture_handle, width, height };
	return t;
}

void texture_unload(struct texture texture)
{
	glDeleteTextures(1, &texture.texture);
}