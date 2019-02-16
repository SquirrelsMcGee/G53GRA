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

using namespace std;

class MyScene :
	public Scene
{
public:
	MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight);
	~MyScene();

	void AddObject(WorldObject *obj);

	Cube *cube;
	
	XInputController *xInput;
	XINPUT_STATE state;
	SHORT lx, ly, rx, ry;

	void Update(const double& deltaTime);
	Tetrahedron *tetra;

private:
	void Initialise();
	void Projection();

	vector<WorldObject*> *objectsList = new vector<WorldObject*>;
};
/*
int width, height = 0;

void setup();
void draw();
int main(int argc, char **argv);
void checkGLError();                        // Prints any OpenGL errors to console
*/