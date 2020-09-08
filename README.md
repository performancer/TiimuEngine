<b>HOW TO USE</b>
```c++
#include "engine/engine.h"

class game : public engine
{
private:
	class graphics _graphics;
	class shader _shader;
	struct texture _texture;
	int _screen_width = 800;
	int _screen_height = 450;
public:
	void initialize() override
	{
		_graphics.set_render_target(0, _screen_width, _screen_height);

		_shader.load("shader.vert", "shader.frag");
		_shader.use();
		_shader.uniform("width", _screen_width);
		_shader.uniform("height", _screen_height);
	}

	void load_content() override
	{
		_texture = texture_load("example.bmp");
	}

	void unload_content() override
	{
		texture_unload(_texture);
		_shader.unload();
	}

	void update(double delta) override
	{
		//TODO: game logic
	}

	void draw(double delta) override
	{
		_graphics.clear(0.0f, 0.0f, 0.0f);
		struct rectangle destination = { 0, 0, _texture.width, _texture.height };
		struct rectangle source = { 0, 0, _texture.width, _texture.height };
		_graphics.draw(_texture, destination, source, false);
		_graphics.render();
	}
};

int main()
{
	class game game;
	game.run(800, 450, "game");
}
```