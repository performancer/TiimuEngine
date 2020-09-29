#include "polygon.h"
#include <algorithm>
#include <limits>
#include <math.h>

Polygon::Polygon(std::vector<Vector> vertices)
{
	_vertices = vertices;
}

Polygon::~Polygon()
{

}

int Polygon::VertexCount() const
{
	return _vertices.size();
}

Vector Polygon::Vertex(int i) const
{
	return _vertices.at(i);
}

Vector Polygon::Edge(int i) const
{
	return Vertex((i + 1) % VertexCount()) - Vertex(i);
}

Vector Polygon::Normal(Vector edge) const
{
	Vector normal = { -edge.x, edge.y };
	normal.Normalize();

	if (edge.Cross(normal) > 0)
		return normal.Scale(-1.0);

	return normal;
}

Extremities Polygon::Projections(Vector axis) const
{
	float highest = std::numeric_limits<float>::min();
	float lowest = std::numeric_limits<float>::max();

	for (int i = 0; i < VertexCount(); i++)
	{
		float length = Vertex(i).Dot(axis);

		highest = std::max(length, highest);
		lowest = std::min(length, lowest);
	}

	return { highest, lowest };
}

Extremities Polygon::Projections(Circle circle, Vector axis) const
{
	float highest = std::numeric_limits<float>::min();
	float lowest = std::numeric_limits<float>::max();

	for (int j = 0; j < VertexCount(); j++)
	{
		Vector edge2 = Edge(j);

		float angle = atan2(edge2.y, edge2.x);

		Vector endpoint = {
			circle.x + circle.radius * cos(angle),
			circle.y + circle.radius * sin(angle)
		};

		float length = endpoint.Dot(axis);

		highest = std::max(length, highest);
		lowest = std::min(length, lowest);
	}

	return { highest, lowest };
}

bool Polygon::Collides(Polygon other) const
{
	for (int i = 0; i < VertexCount(); i++)
	{
		Vector normal = Normal(Edge(i));

		Extremities selfProj = Projections(normal);
		Extremities otherProj = other.Projections(normal);

		if (otherProj.highest - selfProj.lowest > 0 && otherProj.lowest - selfProj.highest > 0)
			return false;

		if (otherProj.highest - selfProj.lowest < 0 && otherProj.lowest - selfProj.highest < 0)
			return false;
	}

	return true;
}

bool Polygon::Collides(Circle circle) const
{
	for (int i = 0; i < VertexCount(); i++)
	{
		Vector normal = Normal(Edge(i));

		Extremities selfProj = Projections(normal);
		Extremities otherProj = Projections(circle, normal);

		if (otherProj.highest - selfProj.lowest > 0 && otherProj.lowest - selfProj.highest > 0)
			return false;

		if (otherProj.highest - selfProj.lowest < 0 && otherProj.lowest - selfProj.highest < 0)
			return false;
	}

	return true;
}