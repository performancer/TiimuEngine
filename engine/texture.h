#pragma once

struct texture
{
	unsigned int texture;
	unsigned short width, height;
};

struct texture texture_load(const char* path);
void texture_unload(struct texture texture);