#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "Functions.h"

using namespace std;

class ObjectFileReader
{
public:
	ObjectFileReader(string &filePath);
	~ObjectFileReader();

	void Load();

	vector<Vertex*> vertices;
	vector<float*> textureCoordinates;
	vector<Vertex*> normals;
	vector<int**> faces;
	vector<int> faceMaterials;

private:
	string _path;

	Vertex * ParseVector(stringstream &ls);
	float * ParseTextureCoordinate(stringstream& ls);
	int** ParseObjectFace(stringstream& ls);
	
};

