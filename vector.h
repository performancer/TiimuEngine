#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif 

	struct VECTOR {
		float x, y;
	};

	struct VECTOR vector_normalize(struct VECTOR vector);

#ifdef __cplusplus
}
#endif 

#endif
