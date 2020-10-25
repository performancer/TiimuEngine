#include "polygon.h"
#include <algorithm>
#include <limits>
#include <math.h>
#define HIGHEST 0
#define LOWEST 1

Polygon::Polygon(Vector position, std::vector<Vector> vertices)
{
	_position = position;
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
	return _position + _vertices.at(i);
}

Vector Polygon::Edge(int i) const
{
	return Vertex((i + 1) % VertexCount()) - Vertex(i);
}

Vector Polygon::Normal(Vector edge) const
{
	Vector normal = { -edge.y, edge.x };
	normal = normal.Normalize();

	if (edge.Cross(normal) > 0)
		return normal.Scale(-1.0);

	return normal;
}

std::tuple<float, float> Polygon::Projections(Vector axis) const
{
	float highest = -std::numeric_limits<float>::max();
	float lowest = std::numeric_limits<float>::max();

	for (int i = 0; i < VertexCount(); i++)
	{
		float length = axis.Dot(Vertex(i));
		highest = std::max(length, highest);
		lowest = std::min(length, lowest);
	}

	return std::tuple<float, float>{highest, lowest};
}

float Polygon::Distance(float minA, float maxA, float minB, float maxB) const
{
	if (minA < minB)
		return minB - maxA;

	return minA - maxB;
}

std::tuple<float, float> Polygon::Projections(Circle circle, Vector axis) const
{
	float highest = -std::numeric_limits<float>::max();
	float lowest = std::numeric_limits<float>::max();

	for (int i = 0; i < VertexCount(); i++)
	{
		Vector edge2 = Edge(i);

		float angle = atan2(edge2.y, edge2.x);

		Vector endpoint = {
			circle.x + circle.radius * cos(angle),
			circle.y + circle.radius * sin(angle)
		};

		float length = endpoint.Dot(axis);

		highest = std::max(length, highest);
		lowest = std::min(length, lowest);
	}

	return std::tuple<float, float>{highest, lowest};
}

bool Polygon::Collides(Polygon other) const
{
	for (int i = 0; i < VertexCount(); i++)
	{
		auto edge = Edge(i);
		auto normal = Normal(edge);
		auto selfProj = Projections(normal);
		auto otherProj = other.Projections(normal);

		auto distance = Distance(
			(float)std::get<LOWEST>(selfProj), 
			(float)std::get<HIGHEST>(selfProj),
			(float)std::get<LOWEST>(otherProj),
			(float)std::get<HIGHEST>(otherProj));

		if(distance > 0)
			return false;
	}

	return true;
}

bool Polygon::Collides(Circle circle) const
{
	for (int i = 0; i < VertexCount(); i++)
	{
		auto normal = Normal(Edge(i));
		auto selfProj = Projections(normal);
		auto otherProj = Projections(circle, normal);

		auto distance = Distance(
			(float)std::get<LOWEST>(selfProj),
			(float)std::get<HIGHEST>(selfProj),
			(float)std::get<LOWEST>(otherProj),
			(float)std::get<HIGHEST>(otherProj));

		if (distance > 0)
			return false;
	}

	return true;
}