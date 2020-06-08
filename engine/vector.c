#include "vector.h"
#include <math.h>

float vector_distance(struct vector vector)
{
	return (float)sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

struct vector vector_scale(struct vector vector, float multiplier)
{
	vector.x *= multiplier;
	vector.y *= multiplier;
	return vector;
}

struct vector vector_normalize(struct vector vector)
{
	return vector_scale(vector, 1.0f / vector_distance(vector));
}