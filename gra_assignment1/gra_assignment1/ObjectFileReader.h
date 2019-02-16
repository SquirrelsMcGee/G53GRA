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

private:
	string _path;

	Vertex * ParseVector(stringstream &ls);
	
};

