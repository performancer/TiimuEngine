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

class engine
{
private:
	void _do_initialize(int width, int height, const char* title);
	void _do_update(double delta);
	void _do_draw(double delta);
	void _cleanup();
public:
	void run(int width, int height, const char* title);
	virtual void initialize() = 0;
	virtual void load_content() = 0;
	virtual void unload_content() = 0;
	virtual void update(double delta) = 0;
	virtual void draw(double delta) = 0;
};