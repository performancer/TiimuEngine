#pragma once

void input_register(int key, int action);
void input_flush();

int key_down(int key);
int key_up(int key);
int key_pressed(int key);
int key_released(int key);

struct vector get_mouse_position();
void on_mouse_press(struct GLFWwindow *window, int button, int action, int mods);
void set_mouse_button_callback(void *callback);