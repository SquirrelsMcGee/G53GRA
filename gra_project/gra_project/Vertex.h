#pragma once

/* This is a class that is mainly used to store Vertex points for use in other classes
** A Vertex point is simply defined as 3 floating point coordinates in (x,y,z) space
** This class is also used as a generic store of 3 floating point values for other uses,
** such as orientation around (rx,ry,rz), and scale in (x,y,z)
*/
class Vertex
{
public:
	Vertex();
	Vertex(float a, float b, float c);
	~Vertex();

	float x, y, z;
};
