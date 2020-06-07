#pragma once

#include <gl\glut.h>

#include "Vertex.h"
#include "ColorRGB.h"

class Triangle
{
public:
	/* Functions */
	Triangle();
	Triangle(Vertex *v1, Vertex *v2, Vertex *v3);
	Triangle(Vertex *v1, Vertex *v2, Vertex *v3, ColorRGB *c1, ColorRGB *c2, ColorRGB *c3);
	~Triangle();

	void Render();

	void setAllColor(ColorRGB *c);

	/* Variables */
	Vertex *v1, *v2, *v3;
	ColorRGB *c1, *c2, *c3;
};

