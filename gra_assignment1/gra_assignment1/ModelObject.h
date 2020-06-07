#pragma once
#include "WorldObject.h"
#include "Face.h"
#include "Functions.h"
#include "ObjectFileReader.h"

class ModelObject :
	public WorldObject
{
public:
	ModelObject(MyScene *scene, string filePath, Vertex * color, int winding);
	~ModelObject();
	void Display();
	void Update(const double& deltaTime);

	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);

	void setScale(Vertex * size);
	void setPosition(Vertex * position);
	void setOrientation(Vertex * orientation);

	Vertex * vSize;
	Vertex * vPosition;
	Vertex * vOrientation;

	MyScene *scene;

	vector<Vertex*> vertices;
	vector<Vertex*> normals;
	vector<Face*> faces;
	vector<float*> textureCoordinates;
	vector<int> faceMaterials;

	Vertex *tempV;
	Vertex * defaultColor;

	ObjectFileReader * objectFileReader;
	string _obj_path;
	string _tex_path;
	string _tex_path2;

	int _texID;
	int _texID2;


	void Render();
private:

	void RenderFace(Face * face);
	void RenderVertex(int vertexIndex);
	void RenderNormal(int normalIndex);
	void RenderMaterial(int textureIndex);

	GLboolean _iKey, _jKey, _kKey, _lKey, _oKey, _uKey;
	GLboolean _plusKey, _minusKey, _upKey, _downKey, _leftKey, _rightKey, _pageUp, _pageDn;
	GLboolean _flagReset, _flagAutospin;

	GLfloat *_mat_ambient, *_mat_diffuse, *_mat_specular, *_mat_shininess;
};

