#pragma once
#include <cstdint>

struct Point
{
	int x, y;
	bool operator==(Point rhs);
	bool operator!=(Point rhs);
	uint64_t Hash();
};