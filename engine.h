#include "include.h"

#ifdef __cplusplus
extern "C" {
#endif 
	void initialize(int width, int height, const char* title);

	struct TEXTURE loadTexture(const char* filename);
	void unloadTexture(struct TEXTURE texture);

	void run(void(*update)(float), void(*draw)(float));

	void clear(float r, float g, float b);
	void drawSprite(struct TEXTURE texture, struct RECTANGLE destination, struct RECTANGLE source, int flipped);
	void setRenderTarget(unsigned int framebuffer, unsigned int width, unsigned int height);
	void render();

#ifdef __cplusplus
}
#endif 