#pragma once
#include "texture.h"
#include "render_target.h"
#include "shader.h"
#include "graphics.h"
#include "input.h"
#include "keys.h"
#include "frame_counter.h"

#include "physics/vector.h"
#include "physics/rectangle.h"
#include "physics/point.h"

class Engine
{
private:
	void _do_initialize(int width, int height, const char* title);
	void _setup_viewport();
	double _deltatime();
public:
	int ViewportWidth() const;
	int ViewportHeight() const;
	int WindowWidth() const;
	int WindowHeight() const;

	void Run(int width, int height, const char* title);
	virtual void Initialize() = 0;
	virtual void LoadContent() = 0;
	virtual void UnloadContent() = 0;
	virtual void Update(double delta) = 0;
	virtual void Draw(double delta) = 0;
};