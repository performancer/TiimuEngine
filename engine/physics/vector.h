#pragma once

struct Vector
{
	float x, y;

	Vector operator-(Vector other);

	float Cross(Vector other) const;
	float Dot(Vector other) const;
	Vector Scale(float multiplier) const;
	Vector Normalize() const;
	float Distance() const;
};