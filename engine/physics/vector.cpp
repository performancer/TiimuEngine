#include "vector.h"
#include <math.h>

Vector Vector::operator-(Vector rhs)
{
	return { x - rhs.x, y - rhs.y };
}

float Vector::Cross(Vector other) const
{
	return x * other.y - y * other.x;
}

float Vector::Dot(Vector other) const
{
	return x * other.x + y * other.y;
}

Vector Vector::Scale(float multiplier) const
{
	Vector vector = { x, y };
	vector.x *= multiplier;
	vector.y *= multiplier;

	return vector;
}

Vector Vector::Normalize() const
{
	return Scale(1.0f / Distance());
}

float Vector::Distance() const
{
	return (float)sqrt(pow(x, 2) + pow(y, 2));
}
