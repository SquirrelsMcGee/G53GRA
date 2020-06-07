#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "Functions.h"
#include "Face.h"

/* This class is used to read Wavefront *.obj static mesh files 
** Mesh files should be placed in the ../Model/ folder
** Input: 
		std::string &filePath >> A relative path from the execution directory
		to the mesh file
** Output:
	-	std::vector<Vertex*> vertices >> A list of vertices as defined by the 
		mesh file in order of definition
	-	std::vector<Vertex*> normals >> A list of normal vectors as defined by 
		the mesh file
	-	std::vector<Face*> faces >> A list of Face objects as defined by the
		mesh file
	-	std::vector<float*> textureCoordinates >> A list of arrays (of length 2)
		that contain texturecoordinates (0 = x, 1 = y), as defined by the mesh 
		file
	-	std::vector<int> faceMaterials >> A list of materials used by the model 
		as defined by the mesh file ##This is currently unused
**
** More information on the Wavefront mesh file standard can be found here:
** https://en.wikipedia.org/wiki/Wavefront_.obj_file#Other_geometry_formats
*/
class ObjectFileReader
{
public:
	ObjectFileReader(std::string &filePath);
	~ObjectFileReader();

	/* Function to begin parsing the file */
	void Load();

	/* Output vectors */
	std::vector<Vertex*> vertices;
	std::vector<Vertex*> normals;
	std::vector<Face*> faces;
	std::vector<float*> textureCoordinates;
	std::vector<int> faceMaterials;

private:
	std::string _path; // file path

	/* These functions used to parse each data group */
	Vertex * ParseVector(std::stringstream &ls);
	float * ParseTextureCoordinate(std::stringstream &ls);
	Face * ParseObjectFace(std::stringstream &ls);
	
};

