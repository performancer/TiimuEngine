<b>HOW TO USE</b>
```c++
#include "engine/engine.h"

class shader shader;
struct texture texture;
int screen_width = 800;
int screen_height = 450;

void update(double delta)
{
	//TODO: game logic
}

void draw(double delta)
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
	shader.load("shader.vert", "shader.frag");
	shader.use();

	texture = texture_load("texture.bmp");

	engine_run(update, draw);

	texture_unload(texture);
	shader.unload();
}
```
