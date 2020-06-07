#pragma once

#include <vector>
#include "Functions.h"
#include "XInputController.h"

#ifndef ___MyScene__
#define ___MyScene__
#endif

#ifdef __APPLE__                        // if OS X
#include <glut/glut.h>                  // include freeglut libraries
#else                                   // if Windows
#include <gl/glut.h>                    // include freeglut libraries
#endif

class WorldObject;
class MySphere;
class Tetrahedron;
class Cube;
class ModelObject;

using namespace std;

class MyScene :
	public Scene
{
public:
	MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight);
	~MyScene();

	void AddObject(WorldObject *obj);

	Cube *cube;
	
	void XInputUpdate();
	int xInputId = 1;
	XInputController *xInput;
	XINPUT_STATE state;
	float lx, ly, rx, ry;
	int lt, rt;
	bool xInputEnabled = false;

	void Update(const double& deltaTime);
	Tetrahedron *tetra;

private:
	void Initialise();
	void Projection();

	vector<WorldObject*> *objectsList = new vector<WorldObject*>;
};