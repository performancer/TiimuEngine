<b>HOW TO USE</b>
```c++
#include "engine/engine.h"

class game : public engine
{
private:
	class shader shader;
	struct texture texture;
	int screen_width = 800;
	int screen_height = 450;
public:
	void initialize() override
	{
		graphics_set_render_target(0, screen_width, screen_height);

		shader.load("shader.vert", "shader.frag");
		shader.use();
		shader_uniform("width", screen_width);
		shader_uniform("height", screen_height);
	}

	void load_content() override
	{
		texture = texture_load("example.bmp");
	}

	void unload_content() override
	{
		texture_unload(texture);
		shader.unload();
	}

	void update(double delta) override
	{
		//TODO: game logic
	}

	void draw(double delta) override
	{
		graphics_clear(0.0f, 0.0f, 0.0f);
		struct rectangle destination = { 0, 0, texture.width, texture.height };
		struct rectangle source = { 0, 0, texture.width, texture.height };
		graphics_draw(texture, destination, source, false);
		graphics_render();
	}
};

int main()
{
	class game game;
	game.run(800, 450, "game");
}
```