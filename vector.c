#include "vector.h"
#include <math.h>

float vector_distance(struct VECTOR vector) {
	return (float)sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

struct VECTOR vector_scale(struct VECTOR vector, float multiplier) {
	vector.x *= multiplier;
	vector.y *= multiplier;
	return vector;
}

struct VECTOR vector_normalize(struct VECTOR vector) {
	return vector_scale(vector, 1.0f/vector_distance(vector));
}