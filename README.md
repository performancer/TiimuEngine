<b>HOW TO USE</b>
```
#include "engine/engine.h"

struct texture texture;
int screen_width = 800;
int screen_height = 450;

void update(float delta)
{
	//TODO: game logic
}

void draw(float delta)
{
	graphics_set_render_target(0, screen_width, screen_height);
	shader_uniform("width", screen_width);
	shader_uniform("height", screen_height);
	graphics_clear(0.0f, 0.0f, 0.0f);
	struct rectangle destination = { 0, 0, texture.width, texture.height };
	struct rectangle source = { 0, 0, texture.width, texture.height };
	graphics_draw(texture, destination, source, false);
	graphics_render();
}

int main()
{
	engine_initialize(screen_width, screen_height, "game");
	shader_load("shader.vert", "shader.frag");
	texture = texture_load("texture.bmp");

	engine_run(update, draw);

	texture_unload(texture);
	shader_delete();
}
```
