#include "Face.h"



Face::Face()
{
	/* Create the vector used to store the Vertex points that define the face */
	faceData = new std::vector<Vertex *>;
}


Face::~Face()
{
}
