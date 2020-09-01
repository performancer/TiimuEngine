#ifndef _INPUT_H_
#define _INPUT_H_

#ifdef __cplusplus
extern "C" 
{
#endif 

	void input_register(int key, int action);
	void input_flush();

	int key_down(int key);
	int key_up(int key);
	int key_pressed(int key);
	int key_released(int key);

#ifdef __cplusplus
}
#endif 
#endif