#include "ObjectFileReader.h"


ObjectFileReader::ObjectFileReader(std::string &filePath)
{
	_path = filePath;
}


ObjectFileReader::~ObjectFileReader()
{
}

void ObjectFileReader::Load() {
	/* In this function, a *.obj file is opened and parsed for data points */
	
	/* Create the filestream by opening the file */
	std::ifstream fileStream(_path, std::ios_base::in);

	/* If file read failed, then output an error */
	if (!fileStream) {
		std::cout << "Error opening '" << _path << "'" << std::endl;
		return;
	}

	/* These variables used for material rendering */
	bool noRender = false;
	int currentMaterial = -1;

	std::string line;
	while (getline(fileStream, line)) {
		// skip line if nothing there or if line is commented
		if (line.length() == 0 || line[0] == '#') continue;

		std::stringstream lineStream(line);
		std::string firstWord;
		lineStream >> firstWord;

		// skip if no first word found, just in case
		if (firstWord.length() == 0) continue;

		if (firstWord == "v") {
			// Line denotes a vertex
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
			//faceMaterials.push_back(0);

		}
		else if (firstWord == "usemtl") {
			// Line denotes a material name
			std::string materialName;
			lineStream >> materialName;
			if (materialName == "material_norender") {
				noRender = true;
				currentMaterial = -1;
			}
			else {
				noRender = false;
				//currentMaterial = //faceMaterials.end()++ ;
			}
		}
		
	}
	fileStream.close();
}

Vertex * ObjectFileReader::ParseVector(std::stringstream &ls) {
	float x, y, z;
	ls >> x >> y >> z;
	return new Vertex(x, y, z);
}

float * ObjectFileReader::ParseTextureCoordinate(std::stringstream &ls) {
	float x, y;
	ls >> x >> y;
	return new float[2]{ x, y };
}

Face * ObjectFileReader::ParseObjectFace(std::stringstream &ls) {
	/* This function creates a new object face, it is able to determine
	** if a face is composed of either 3 or 4 vertices, and act accordingly
	*/

	Face * face = new Face(); // Create a new face object
	std::string encodedFace; // Face in string format from the file

	while (ls >> encodedFace) {

		Vertex * data = new Vertex();
		data->x = -1; // Index of vertex in vertices vector
		data->y = -1; // Index of texture coordinates in textures vector
		data->z = -1; // Index of normal in normals vector

		/* Find the first and second '/' characters */
		size_t firstPos = encodedFace.find('/');
		size_t secondPos = encodedFace.find('/', firstPos + 1);

		/* Check if the texture coordinate and normal vector exists */
		bool textureCoordinateExists = secondPos - firstPos > 1;
		bool normalExists = encodedFace.length() - secondPos > 1;

		/* Convert the string values to integers */
		data->x = (float)std::stoi(encodedFace.substr(0, firstPos).c_str()) - 1;

		if (textureCoordinateExists)
			data->y = (float)std::stoi(encodedFace.substr(firstPos + 1, secondPos - firstPos).c_str()) - 1;

		if (normalExists)
			data->z = (float)std::stoi(encodedFace.substr(secondPos + 1, encodedFace.length() - secondPos).c_str()) - 1;

		/* Add vertex to the face data */
		face->faceData->push_back(data);
	}

	return face;
}