#ifndef _WINDOW_H_
#define _WINDOW_H_

struct GLFWwindow* get_window();
struct GLFWwindow* window_setup(int width, int height, const char* title);

#endif