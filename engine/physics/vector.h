#pragma once

struct Vector
{
	float x, y;

	friend Vector operator+(const Vector& lhs, const Vector& rhs);
	friend Vector operator-(const Vector& lhs, const Vector& rhs);

	float Cross(Vector other) const;
	float Dot(Vector other) const;
	Vector Scale(float multiplier) const;
	Vector Normalize() const;
	float Magnitude() const;
};