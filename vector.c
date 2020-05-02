#include "vector.h"
#include <math.h>

float vector_distance(struct VECTOR vector) {
	return (float)sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

struct VECTOR vector_divide(struct VECTOR vector, float divisor) {
	vector.x /= divisor;
	vector.y /= divisor;
	return vector;
}

struct VECTOR vector_normalize(struct VECTOR vector) {
	return vector_divide(vector, vector_distance(vector));
}