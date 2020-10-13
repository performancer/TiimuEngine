#include "texture.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "io/image.h"

texture texture_load(const char* path)
{
	unsigned int width, height;
	unsigned char* data = loadImage(path, &width, &height);

	texture text = texture_load(width, height, data);

	if (data == 0)
	{
		printf("ERROR::TEXTURE::LOADING_FAILED\n%s\n", path);
		exit(1);
	}

	free(data);

	return text;
}

struct texture texture_load(unsigned int width, unsigned int height, const unsigned char* data)
{
	unsigned int texture_handle;
	glGenTextures(1, &texture_handle);
	glBindTexture(GL_TEXTURE_2D, texture_handle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);

	return { texture_handle, (unsigned short)width, (unsigned short)height };
}

void texture_unload(struct texture texture)
{
	glDeleteTextures(1, &texture.texture);
}