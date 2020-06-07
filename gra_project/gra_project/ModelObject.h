#pragma once
#include "WorldObject.h"
#include "Face.h"
#include "Functions.h"
#include "ObjectFileReader.h"

/* This is a class that is used to render the output of ObjectFileReader
** which produces vectors of vertices, normals, faces, texture coordinates and
** face materials
** Currently this only supports single *.bmp textures
*/
class ModelObject :
	public WorldObject
{
public:
	ModelObject(MyScene *scene, int id, std::string objectName, ColorRGB *color, std::string fileName ,int winding);
	~ModelObject();
	void Display();

	int _texId; // The texture id of the applied texture

private:
	/* Functions used to render the mesh and it's attributes to the screen */
	void Render();

	void RenderFace(Face * face);
	void RenderVertex(int vertexIndex);
	void RenderNormal(int normalIndex);
	void RenderMaterial(int texCoordIndex);

	std::string _tex_path; // The path of the initial texture file
	

	/* ObjectFileReader loads a Wavefront *.obj file and returns the result
	** to the following vectors
	*/
	ObjectFileReader * objectFileReader;
	std::string _obj_path;

	/* These vectors contain the various data points obtained by ObjectFileReader */
	/** This class utilises Face objects, the reason for this is that the Wavefront
	** format does allows for both Quad faces and Triangle faces to exist in the same
	** mesh, for simplicity, I use the Face class rather than a combination of Quad and Triangle
	*/
	std::vector<Face*> faces;				// Defined as 3 or more Vertex points
	std::vector<Vertex*> vertices;			// Defined by 3 floating point values
	std::vector<float*> textureCoordinates;	// Defined as 2 floating point values
	std::vector<Vertex*> normals;			// Defined by 3 floating point values
	std::vector<int> faceMaterials;			// Defined as a 1 integer, currently not used
	/* The faces vector is used as a list of index positions for the other vectors
	** to store index positions of objects,
	** x = vertices index
	** y = textureCoordinates index
	** z = normals index
	*/

	/* These variables are used to define the light characteristics of the model */
	GLfloat mat_ambient[4] = { 0.f, 0.f, 0.f, 1.f };
	GLfloat mat_diffuse[4] = { 0.f, 0.f, 0.f, 1.f };
	GLfloat mat_specular[4] = { 0.f, 0.f, 0.f, 1.f };
	GLfloat mat_shininess[1] = { 0 }; // 0-128
};

