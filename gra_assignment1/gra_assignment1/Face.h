#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "Vertex.h"
#include "Functions.h"
class Face
{
public:
	Face();
	~Face();

	vector<Vertex*> *faceData;
	//vector<Vertex*> *vertices;
	//vector<Vertex*> *vertices;
};

