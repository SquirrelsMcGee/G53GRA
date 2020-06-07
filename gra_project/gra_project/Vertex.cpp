#include "Vertex.h"



Vertex::Vertex() {
	/* Set default coordinates to 0.f */
	x = 0.f;
	y = 0.f;
	z = 0.f;
}

Vertex::Vertex(float f1, float f2, float f3) {
	/* Set coordinates (x,y,z) from given values */
	x = f1;
	y = f2;
	z = f3;
}


Vertex::~Vertex()
{
}
