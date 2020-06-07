#pragma once

#include "GL\glut.h"

#include <iostream>
#include "Vertex.h"
#include "ColorRGB.h"

/* This is a class that is used to store a Quad, a polygon that is composed of 4 Vertex points
** It is similar to the Face and Triangle classes
** When using, make sure that the order v1-v4 for a Quad polygon is consistent in winding
** This class also stores colour information in ColorRGB format
** This class provides Texture coordinates
*/
class Quad
{
public:
	/* Functions */
	Quad();
	Quad(Vertex *v1, Vertex *v2, Vertex *v3, Vertex *v4);
	Quad(Vertex *v1, Vertex *v2, Vertex *v3, Vertex *v4, ColorRGB *c1, ColorRGB *c2, ColorRGB *c3, ColorRGB *c4);
	~Quad();

	void Render();
	void PrintC();
	void PrintV();

	void setAllColor(ColorRGB *c);

	/* Variables */
	Vertex *v1, *v2, *v3, *v4;
	ColorRGB *c1, *c2, *c3, *c4;
	float *tx;
	int winding;
	float tcX = 0.0f;
	float tcY = 0.0f;
};

