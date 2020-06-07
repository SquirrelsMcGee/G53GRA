#pragma once

#include <vector>
#include "Vertex.h"
#include "Functions.h"

/* This is a class that is used to store faces as defined by Wavefront *.obj files
** In this application, a face is either 3 or 4 Vertex points
*/
class Face
{
public:
	Face();
	~Face();

	std::vector<Vertex*> *faceData;
};

