#pragma once
#include "vector.h"
#include "rectangle.h"
#include "texture.h"
#include "render_target.h"
#include "shader.h"
#include "graphics.h"
#include "input.h"
#include "keys.h"
#include "frame_counter.h"
#include "audio/audio.h"
#include "point.h"

class engine
{
private:
	Point _viewport;
	void _do_initialize(int width, int height, const char* title);
	void _do_update(double delta);
	void _do_draw(double delta);
	double _deltatime();
public:
	int GetViewportWidth() const;
	int GetViewportHeight() const;

	void Run(int width, int height, const char* title);
	virtual void Initialize() = 0;
	virtual void LoadContent() = 0;
	virtual void UnloadContent() = 0;
	virtual void Update(double delta) = 0;
	virtual void Draw(double delta) = 0;
};