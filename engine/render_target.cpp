#include "render_target.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>

struct render_target render_target_create(unsigned short width, unsigned short height)
{
	struct render_target target = { 0, width, height, 0 };

	glGenFramebuffers(1, &target.framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, target.framebuffer);

	glGenTextures(1, &target.texture);

	glBindTexture(GL_TEXTURE_2D, target.texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, target.width, target.height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, target.texture, 0);

	unsigned int draw_buffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, draw_buffers);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("ERROR::RENDER_TARGET::CREATING_FRAMEBUFFER_FAILED!");
		exit(1);
	}

	return target;
}