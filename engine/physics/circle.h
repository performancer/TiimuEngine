#pragma once

struct Circle
{
	float x;
	float y;
	float radius;

	bool Collides(Circle other);
};
