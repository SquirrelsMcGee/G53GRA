#pragma once
#include <vector>
#include <stdio.h>
#include <iostream>


#include "Triangle.h"
#include "Functions.h"
#include "MyScene.h"

using namespace std;

class WorldObject :
	public DisplayableObject,
	public Animation,
	public Input
{
public:
	WorldObject(MyScene *scene, int id, string type, int colour);
	//WorldObject(MyScene *scene, int id, string type, int colour, WorldObject *parent);
	~WorldObject();

	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);

	vector<WorldObject*> *newObjs;

private:
	//void DrawAllTriangles();
	//void CreateTriangles();

	MyScene *scene;

	vector<Triangle*> polygons;

	GLboolean _iKey, _jKey, _kKey, _lKey, _oKey, _uKey;
	GLboolean _plusKey, _minusKey, _upKey, _downKey, _leftKey, _rightKey;
	GLboolean _flagReset, _flagAutospin;
};

