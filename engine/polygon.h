#pragma once
#include <vector>
#include "vector.h"
#include "circle.h"

struct Extremities
{
	float highest;
	float lowest;
};

class Polygon
{
private:
	std::vector<Vector> _vertices;

	int VertexCount() const;
	Vector Vertex(int i) const;
	Vector Edge(int i) const;

	Vector Normal(Vector edge) const;
	Extremities Projections(Vector axis) const;
	Extremities Projections(Circle circle, Vector axis) const;

public:
	Polygon(std::vector<Vector> vertices);
	~Polygon();

	bool Collides(Polygon other) const;
	bool Collides(Circle circle) const;
};