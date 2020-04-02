#include "input.h"

bool buffer[350];
int size;

bool isKeyDown(int key) {
	return buffer[key];
}

bool isKeyUp(int key) {
	return !buffer[key];
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {	
	switch (action) {
	case GLFW_RELEASE: buffer[key] = false; break;
	case GLFW_PRESS: buffer[key] = true; break;
	}
}