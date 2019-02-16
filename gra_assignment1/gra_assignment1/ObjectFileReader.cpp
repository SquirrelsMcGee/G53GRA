#include "ObjectFileReader.h"



ObjectFileReader::ObjectFileReader(string &filePath)
{
	_path = filePath;
}


ObjectFileReader::~ObjectFileReader()
{
}

void ObjectFileReader::Load() {
	ifstream fileStream(_path, ios_base::in);

	if (!fileStream) {
		cout << "Error opening '" << _path << "'" << endl;
		return;
	}

	string line;
	while (getline(fileStream, line)) {
		if (line.length() == 0 || line[0] == '#') continue; // skip line if nothing there or if line is commented

		stringstream lineStream(line);
		string firstWord;
		lineStream >> firstWord;

		if (firstWord.length() == 0) continue; // skip if no first word found

		if (firstWord == "v") {
			// Line denotes a vertex, add to list
			vertices.push_back(ParseVector(lineStream));
		}
		else if (firstWord == "vt") {
			// Line denotes a texture coordinate
		}
		else if (firstWord == "vn") {
			// Line denotes a normal
		}
		else if (firstWord == "f") {
			// Line denotes a face
		}
		else if (firstWord == "usemtl") {
			// Line denotes a material name
		}
	}
	fileStream.close();
}

Vertex * ObjectFileReader::ParseVector(stringstream &ls) {
	float x, y, z;
	ls >> x >> y >> z;
	return new Vertex(x, y, z);
}