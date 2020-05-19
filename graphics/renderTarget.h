struct RENDER_TARGET {
	unsigned int framebuffer;
	unsigned short width, height;
	unsigned int texture;
};

#ifdef __cplusplus
extern "C" {
#endif 

	struct RENDER_TARGET createRenderTarget(unsigned short width, unsigned short height);

#ifdef __cplusplus
}
#endif 