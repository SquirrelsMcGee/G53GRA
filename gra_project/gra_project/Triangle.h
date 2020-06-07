#pragma once

#include "GL\glut.h"

#include "Vertex.h"
#include "ColorRGB.h"

/* This is a class that is used to store a Triangle, a polygon that is composed of 3 Vertex points
** It is similar to the Face and Triangle classes
** When using, make sure that the order v1-v3 for a Triangle polygon is consistent in winding
** This class also stores colour information in ColorRGB format
** This class does not provide Texture coordinates
*/
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

