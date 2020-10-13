#pragma once
#include "physics/point.h"

struct Color
{
	char R, G, B, A;
};

struct texture
{
	unsigned int texture;
	unsigned short width, height;
};

struct texture texture_load(const char* path);
struct texture texture_load(unsigned int width, unsigned int height, const unsigned char* data);
void texture_unload(struct texture texture);