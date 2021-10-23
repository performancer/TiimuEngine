<b>TiimuEngine</b>

TiimuEngine is a very simple 2D engine built on OpenGL. It's a goofy little hobby project to learn more about OpenGL, please do not use this.

This project has been abandoned and will not be developed any longer.

<b>HOW TO USE</b>

Add following files to your project:

shader.frag
```GLSL
#version 330 core

out vec4 color;
in vec2 uv;
uniform sampler2D tex;

void main() {
    color = texture(tex, uv);
}
```

shader.vert
```GLSL
#version 330 core

layout (location = 0) in vec2 vert;
layout (location = 1) in vec2 _uv;
uniform float width;
uniform float height;

out vec2 uv;

void main() {
    uv = _uv;
    gl_Position = vec4(vert.x / (width * 0.5) - 1.0, vert.y / (height * 0.5) - 1.0, 0.0, 1.0);
}
```

Game.h
```c++
#include "engine/engine.h"

class Game : public Engine
{
private:
	class graphics _graphics;
	class shader _shader;
	struct texture _texture;
public:
	void Initialize() override
	{
		//TODO: initialize your game here (this is run before loading content)

		int width = WindowWidth();
		int height = WindowHeight();

		_graphics.set_render_target(0, width, height);

		_shader.load("shader.vert", "shader.frag");
		_shader.use();
		_shader.uniform("width", WindowWidth());
		_shader.uniform("height", WindowHeight());
	}

	void LoadContent() override
	{
		//TODO: load your content here

		_texture = texture_load("example.bmp");
	}

	void UnloadContent() override
	{
		//TODO: unload your content here

		texture_unload(_texture);
		_shader.unload();
	}

	void Update(double delta) override
	{
		//TODO: game logic
	}

	void Draw(double delta) override
	{
		_graphics.clear(0.0f, 0.0f, 0.0f);
		_graphics.draw(_texture, { 0, 0 });
		_graphics.render();
	}
};

int main()
{
	class Game game;
	game.Run(800, 450, "GameName");
}
```

You will also need to include 'example.bmp', 32-bit RGBA bitmap file.
