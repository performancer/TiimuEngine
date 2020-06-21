#ifndef _RENDER_TARGET_H_
#define _RENDER_TARGET_H_

struct render_target
{
	unsigned int framebuffer;
	unsigned short width, height;
	unsigned int texture;
};

#ifdef __cplusplus
extern "C"
{
#endif 

	struct render_target render_target_create(unsigned short width, unsigned short height);

#ifdef __cplusplus
}
#endif
#endif