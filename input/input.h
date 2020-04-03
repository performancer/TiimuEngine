#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GLFW/glfw3.h>

#include "keys.h"

#ifdef __cplusplus
extern "C" {
#endif 

	bool isKeyDown(int key);

#ifdef __cplusplus
}
#endif 

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);