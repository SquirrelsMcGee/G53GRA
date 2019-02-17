#pragma once
#include "WorldObject.h"
#include "Functions.h"
#include "ObjectFileReader.h"
class ModelObject :
	public WorldObject
{
public:
	ModelObject(MyScene *scene, string filePath);
	~ModelObject();
	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);

	MyScene *scene;

	vector<Vertex*> vertices;
	vector<Vertex*> normals;
	vector<float*> textureCoordinates;
	vector<int**> faces;
	vector<int> faceMaterials;

	Vertex *tempV;

	ObjectFileReader * objectFileReader;
	string _path;

	void Render();
private:
	
	//void BeginRender();
	void RenderFace(int ** face);

	GLboolean _iKey, _jKey, _kKey, _lKey, _oKey, _uKey;
	GLboolean _plusKey, _minusKey, _upKey, _downKey, _leftKey, _rightKey;
	GLboolean _flagReset, _flagAutospin;
};

