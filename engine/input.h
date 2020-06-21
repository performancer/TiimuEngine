#ifndef _INPUT_H_
#define _INPUT_H_

#ifdef __cplusplus
extern "C" 
{
#endif 

	void input_register(int key, int action);
	unsigned int is_key_down(int key);
	unsigned int is_key_up(int key);

#ifdef __cplusplus
}
#endif 
#endif