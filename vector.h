#ifndef _VECTOR_H_
#define _VECTOR_H_

struct VECTOR {
	float x, y;
};

#ifdef __cplusplus
extern "C" {
#endif 

	float vector_distance(struct VECTOR vector);
	struct VECTOR vector_divide(struct VECTOR vector, float divisor);
	struct VECTOR vector_normalize(struct VECTOR vector);

#ifdef __cplusplus
}
#endif 

#endif
