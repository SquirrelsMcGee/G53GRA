#pragma once

#include "GL\glut.h"

#include <iostream>
#include "Vertex.h"
#include "ColorRGB.h"

class Quad
{
public:
	/* Functions */
	Quad();
	Quad(Vertex *v1, Vertex *v2, Vertex *v3, Vertex *v4);
	Quad(Vertex *v1, Vertex *v2, Vertex *v3, Vertex *v4, ColorRGB *c1, ColorRGB *c2, ColorRGB *c3, ColorRGB *c4);
	~Quad();

	void Render();

	void setAllColor(Vertex *c);

	/* Variables */
	Vertex *v1, *v2, *v3, *v4;
	Vertex *c1, *c2, *c3, *c4;
	int winding;
	double tcX = 0.0f;
	double tcY = 0.0f;
};

