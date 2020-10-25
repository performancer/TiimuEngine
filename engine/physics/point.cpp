#include "point.h"

bool Point::operator==(Point rhs)
{
	return x == rhs.x && y == rhs.y;
}

bool Point::operator!=(Point rhs)
{
	return !(*this == rhs);
}

uint64_t Point::Hash()
{
	int32_t x = this->x;
	int32_t y = this->y;

	return (((uint64_t)x) << 32) | y;
}