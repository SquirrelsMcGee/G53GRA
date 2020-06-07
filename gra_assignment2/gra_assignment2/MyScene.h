#pragma once

#ifndef ___MyScene__
#define ___MyScene__
#endif

#ifdef __APPLE__                        // if OS X
#include <glut/glut.h>                  // include freeglut libraries
#else                                   // if Windows
#include <gl/glut.h>                    // include freeglut libraries
#endif

#include <vector>
#include <algorithm> 
#include "Functions.h"

class WorldObject;
class SquareObject;

class MyScene : 
	public Scene
{
public:
	MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight);
	~MyScene();

	void AddObject(WorldObject* obj);
	void AddAngle(double theta);
	int squareCount = 0;

private:
	void Initialise();
	void Projection();
	void Update(const double& deltaTime);

	std::vector<WorldObject*> *objectsList;
	std::vector<double> *angles;
};

