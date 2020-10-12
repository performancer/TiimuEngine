#include "circle.h"
#include <cmath>

bool Circle::Collides(Circle rhs)
{
	return sqrt(pow(x - rhs.x, 2) + pow(y - rhs.y, 2)) < radius + rhs.radius;
}
