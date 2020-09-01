#pragma once

struct vector
{
	float x, y;
};

float vector_distance(struct vector vector);
struct vector vector_scale(struct vector vector, float multiplier);
struct vector vector_normalize(struct vector vector);