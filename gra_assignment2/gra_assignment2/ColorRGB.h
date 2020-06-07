#pragma once

#include "Vertex.h"

class ColorRGB :
	public Vertex
{
public:
	ColorRGB();
	ColorRGB(float r, float g, float b);
	~ColorRGB();
};
