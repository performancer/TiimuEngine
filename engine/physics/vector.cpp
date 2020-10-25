#include "vector.h"
#include <math.h>

Vector operator+(const Vector& lhs, const Vector& rhs)
{
	return { lhs.x + rhs.x, lhs.y + rhs.y };
}

Vector operator-(const Vector& lhs, const Vector& rhs)
{
	return { lhs.x - rhs.x, lhs.y - rhs.y };
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
	return Scale(1.0f / Magnitude());
}

float Vector::Magnitude() const
{
	return sqrtf(x * x + y * y);
}
