#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "Functions.h"
#include "Face.h"

using namespace std;

class ObjectFileReader
{
public:
	ObjectFileReader(string &filePath);
	~ObjectFileReader();

	void Load();

	vector<Vertex*> vertices;
	vector<Vertex*> normals;
	vector<Face*> faces;
	vector<float*> textureCoordinates;
	vector<int> faceMaterials;

private:
	string _path;

	Vertex * ParseVector(stringstream &ls);
	float * ParseTextureCoordinate(stringstream &ls);
	Face * ParseObjectFace(stringstream &ls);
	
};

