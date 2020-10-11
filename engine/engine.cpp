#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window.h"

Point _setup_viewport(GLFWwindow* window)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	return { width, height };
}

double engine::_deltatime()
{
	static double time;
	double tmp = glfwGetTime();
	double delta = tmp - time;
	time = tmp;

	return delta;
}

void engine::_do_initialize(int width, int height, const char* title)
{
	GLFWwindow* window = window_setup(width, height, title);

	glewExperimental = GL_TRUE;
	glewInit();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_SCISSOR_TEST);

	_viewport = _setup_viewport(window);

	Initialize();
	LoadContent();
}

void engine::_do_update(double delta)
{
	Update(delta);
}

void engine::_do_draw(double delta)
{
	Draw(delta);
}

int engine::GetViewportWidth() const
{
	return _viewport.x;
}

int engine::GetViewportHeight() const
{
	return _viewport.y;
}

void engine::Run(int width, int height, const char* title)
{
	_do_initialize(width, height, title);

	double delta = _deltatime();

	while (!glfwWindowShouldClose(get_window()))
	{
		delta = _deltatime();
		frame_counter_update(delta);
		glfwPollEvents();
		_do_update(delta);
		_do_draw(delta);
		input_flush();
	}

	glfwTerminate();
}