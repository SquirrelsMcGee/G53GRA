#pragma once
#include <vector>
#include <stdio.h>
#include <iostream>

#include "Functions.h"
#include "MyScene.h"
#include "WorldObject.h"
#include "Cube.h"

using namespace std;

class Tetrahedron :
	public WorldObject
{
public:
	Tetrahedron(MyScene *scene);
	~Tetrahedron();
	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);

	//vector<WorldObject*> *newObjs;

	GLboolean _flagAdd = false;

private:
	void DrawAllTriangles();
	void CreateTriangles();

	void AddCubeToScene();

	MyScene *scene;

	vector<Triangle*> polygons;

	GLboolean _iKey, _jKey, _kKey, _lKey, _oKey, _uKey;
	GLboolean _plusKey, _minusKey, _upKey, _downKey, _leftKey, _rightKey;
	GLboolean _flagReset, _flagAutospin;
	
};

