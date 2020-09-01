#ifndef _TEXTURE_H_
#define _TEXTURE_H_

struct texture
{
	unsigned int texture;
	unsigned int width, height;
};

#ifdef __cplusplus
extern "C"
{
#endif 

	struct texture texture_load(const char* path);
	void texture_unload(struct texture texture);

#ifdef __cplusplus
}
#endif 

#endif