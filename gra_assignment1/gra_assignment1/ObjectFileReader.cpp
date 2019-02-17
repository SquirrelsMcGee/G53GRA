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

	bool noRender = false;

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
			textureCoordinates.push_back(ParseTextureCoordinate(lineStream));
		}
		else if (firstWord == "vn") {
			// Line denotes a normal
			normals.push_back(ParseVector(lineStream));
		}
		else if (firstWord == "f") {
			// Line denotes a face
			if (noRender) continue;
			faces.push_back(ParseObjectFace(lineStream));

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

float * ObjectFileReader::ParseTextureCoordinate(stringstream& ls) {
	float x, y;
	ls >> x >> y;
	return new float[2]{ x, y };
}

int** ObjectFileReader::ParseObjectFace(stringstream& ls) {
	// Limit of triangle-based polygons (3 vertices)
	int ** res = new int*[3];

	for (int i = 0; i < 3; i++) {
		int * vertexIndices = new int[3]{ -1, -1, -1 };
		string encodedFaceVertex;
		ls >> encodedFaceVertex;

		size_t firstPos = encodedFaceVertex.find('/');
		size_t secondPos = encodedFaceVertex.find('/', firstPos + 1);

		bool textureCoordinateExists = secondPos - firstPos > 1;
		bool normalCoordinateExists = encodedFaceVertex.length() - secondPos > 1;

		vertexIndices[0] = stoi(encodedFaceVertex.substr(0, firstPos).c_str()) - 1;

		if (textureCoordinateExists) vertexIndices[1] = stoi(encodedFaceVertex.substr(firstPos + 1, secondPos - firstPos).c_str()) - 1;
		if (normalCoordinateExists) vertexIndices[2] = stoi(encodedFaceVertex.substr(secondPos + 1, encodedFaceVertex.length() - secondPos).c_str()) - 1;

		res[i] = vertexIndices;
	}

	return res;
}