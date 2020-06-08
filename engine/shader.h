#ifndef _SHADER_H_
#define _SHADER_H_

#ifdef __cplusplus
extern "C"
{
#endif 

	void shader_uniform(const char* key, int value);
	void shader_use();
	void shader_delete();
	void shader_load(const char* vertex, const char* fragment);

#ifdef __cplusplus
}
#endif
#endif