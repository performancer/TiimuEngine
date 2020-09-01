#pragma once

void input_register(int key, int action);
void input_flush();

int key_down(int key);
int key_up(int key);
int key_pressed(int key);
int key_released(int key);