#ifndef _VECTOR_H_
#define _VECTOR_H_

struct vector
{
	float x, y;
};

#ifdef __cplusplus
extern "C"
{
#endif 

	float vector_distance(struct vector vector);
	struct vector vector_scale(struct vector vector, float multiplier);
	struct vector vector_normalize(struct vector vector);

#ifdef __cplusplus
}
#endif 
#endif
