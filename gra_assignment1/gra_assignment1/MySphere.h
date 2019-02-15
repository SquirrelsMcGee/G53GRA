#pragma once
#include <vector>
#include <stdio.h>
#include <iostream>

#include "Functions.h"
#include "MyScene.h"
#include "WorldObject.h"

using namespace std;

class MySphere :
	public WorldObject
{
public:
	MySphere(MyScene *scene);
	~MySphere();
	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);

private:
	void DrawAllTriangles();
	void DrawWireframe();
	void Subdivide(int count, Triangle *t);
	void CreatePolygons();

	MyScene *scene;

	vector<Triangle*> polygons;
	int division = 2; // depth of subdivisions, do not go less than 0, else it will crash

	GLboolean _iKey, _jKey, _kKey, _lKey, _oKey, _uKey;
	GLboolean _plusKey, _minusKey, _upKey, _downKey, _leftKey, _rightKey;
	GLboolean _flagReset, _flagAutospin;
};