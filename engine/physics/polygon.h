#pragma once
#include <vector>
#include <tuple>
#include "vector.h"
#include "circle.h"

class Polygon
{
private:
	Vector _position;
	std::vector<Vector> _vertices;

	Vector Edge(int i) const;

	Vector Normal(Vector edge) const;
	std::tuple<float, float> Projections(Vector axis) const;
	std::tuple<float, float> Projections(Circle circle, Vector axis) const;

	float Distance(float minA, float maxA, float minB, float maxB) const;

public:
	int VertexCount() const;
	Vector Vertex(int i) const;

	Polygon(Vector position, std::vector<Vector> vertices);
	~Polygon();

	bool Collides(Polygon other) const;
	bool Collides(Circle circle) const;
};