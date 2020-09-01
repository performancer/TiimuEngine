#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "frame_counter.h"

void _setup_viewport(GLFWwindow* window)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}

void _cleanup()
{
	graphics_cleanup();
	shader_delete();
}

double _deltatime()
{
	static double time;
	double tmp = glfwGetTime();
	double delta = tmp - time;
	time = tmp;

	return delta;
}

void engine_initialize(int width, int height, const char* title)
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

	_setup_viewport(window);
}

void engine_run(void(*update)(double), void(*draw)(double))
{
	double delta = _deltatime();

	while (!glfwWindowShouldClose(get_window()))
	{
		delta = _deltatime();
		frame_counter_update(delta);
		glfwPollEvents();
		update(delta);
		draw(delta);
		input_flush();
	}

	_cleanup();
	glfwTerminate();
}

void engine_resize_viewport(int width, int height)
{
	glViewport(0, 0, width, height);
}

struct vector engine_monitor_resolution()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	struct vector vector = { (float)mode->width, (float)mode->height };
	return vector;
}

