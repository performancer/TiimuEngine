#pragma once

void graphics_clear(float r, float g, float b);
void graphics_draw(struct texture texture, struct rectangle destination, struct rectangle source, int flipped);
void graphics_set_render_target(unsigned int framebuffer, unsigned int width, unsigned int height);
void graphics_render();
void graphics_cleanup();