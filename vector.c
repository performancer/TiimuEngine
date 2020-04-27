#include "vector.h"

struct VECTOR vector_normalize(struct VECTOR vector) {
	float distance = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	vector.x /= distance;
	vector.y /= distance;
	return vector;
}