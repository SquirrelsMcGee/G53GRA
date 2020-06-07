#pragma once

#include "Vertex.h"

/* This class is an extension of the Vertex class
** it is used as a layer of abstraction for storing
** RGB colour values in the same format as a Vertex
** x = red, y = green, z = blue
*/

class ColorRGB :
	public Vertex
{
public:
	ColorRGB();
	ColorRGB(float r, float g, float b);
	~ColorRGB();
};
