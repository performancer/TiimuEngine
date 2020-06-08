#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window.h"

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

float _deltatime(float* time)
{
	float tmp = (float)glfwGetTime();
	float delta = tmp - *time;
	*time = tmp;

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

void engine_run(void(*update)(float), void(*draw)(float))
{
	float time = (float)glfwGetTime();

	while (!glfwWindowShouldClose(get_window()))
	{
		float delta = _deltatime(&time);
		glfwPollEvents();
		update(delta);
		draw(delta);
	}

	_cleanup();
	glfwTerminate();
}

