#include "window.h"
#include <GLFW/glfw3.h>
#include "input.h"

struct GLFWwindow* _window;

struct GLFWwindow* get_window()
{
	return _window;
}

void key_callback(struct GLFWwindow* window, int key, int scancode, int action, int mode)
{
	input_register(key, action);
}

struct GLFWwindow* window_setup(int width, int height, const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	_window = glfwCreateWindow(width, height, title, 0, 0);
	glfwMakeContextCurrent(_window);
	glfwSetKeyCallback(_window, key_callback);

	return _window;
}