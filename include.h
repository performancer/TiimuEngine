#ifndef _INCLUDE_H_
#define _INCLUDE_H_
#include "rectangle.h"
#include "vector.h"
#include "graphics/renderTarget.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "input/keys.h"

#ifdef __cplusplus
extern "C" {
#endif 

	void loadShader(const char* vertex, const char* fragment);
	void shaderParameter(const char* key, int value);

	int isKeyDown(int key);
	int isKeyUp(int key);

#ifdef __cplusplus
}
#endif 
#endif