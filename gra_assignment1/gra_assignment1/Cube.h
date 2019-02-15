#pragma once
#include <vector>
#include <stdio.h>
#include <iostream>

#include "Functions.h"
#include "MyScene.h"
#include "WorldObject.h"

using namespace std;

class Cube :
	public WorldObject
{
public:
	Cube(MyScene *scene);
	~Cube();
	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);
	
	MyScene *scene;

	vector<Triangle*> polygons;
	Triangle *tempT;

	bool drawBothSides = false;

private:
	void DrawAllTriangles();
	void CreatePolygons();

	GLboolean _iKey, _jKey, _kKey, _lKey, _oKey, _uKey;
	GLboolean _plusKey, _minusKey, _upKey, _downKey, _leftKey, _rightKey;
	GLboolean _flagReset, _flagAutospin;
};

