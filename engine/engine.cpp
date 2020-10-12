#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window.h"

void Engine::_do_initialize(int width, int height, const char* title)
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

	_setup_viewport();

	Initialize();
	LoadContent();
}

void Engine::_setup_viewport()
{
	int width, height;
	glfwGetFramebufferSize(get_window(), &width, &height);
	glViewport(0, 0, width, height);
}

double Engine::_deltatime()
{
	static double time;
	double tmp = glfwGetTime();
	double delta = tmp - time;
	time = tmp;

	return delta;
}

int Engine::ViewportWidth() const
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	return viewport[2];
}

int Engine::ViewportHeight() const
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	return viewport[3];
}

int Engine::WindowWidth() const
{
	int width, height;
	glfwGetWindowSize(get_window(), &width, &height);

	return width;
}

int Engine::WindowHeight() const
{
	int width, height;
	glfwGetWindowSize(get_window(), &width, &height);

	return height;
}

void Engine::Run(int width, int height, const char* title)
{
	_do_initialize(width, height, title);

	double delta = _deltatime();

	while (!glfwWindowShouldClose(get_window()))
	{
		delta = _deltatime();
		frame_counter_update(delta);
		glfwPollEvents();
		Update(delta);
		Draw(delta);
		input_flush();
	}

	glfwTerminate();
}