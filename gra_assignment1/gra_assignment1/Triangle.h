#pragma once
#include "Vertex.h"
class Triangle
{
public:
	Triangle();
	Triangle(Vertex *v1, Vertex *v2, Vertex *v3);
	Triangle(Vertex *v1, Vertex *v2, Vertex *v3, Vertex *c1, Vertex *c2, Vertex *c3);
	~Triangle();

	void setAllColor(Vertex *c);

	Vertex *v1, *v2, *v3;
	Vertex *c1, *c2, *c3;
};

