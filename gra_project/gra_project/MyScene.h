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
#include "XInputController.h"

/* Because the following classes utilise the MyScene class
** and thus include MyScene.h, the header file cannot contain
** these dependencies
** Therefore in MyScene.h empty class definitions are created
** and the actual classes are included in MyScene.cpp
*/
class WorldObject;
class PlayerObject;
class SquareObject;
class LightObject;
class Skybox;
class ModelObject;

/* This class is an extension of the provided Scene class with extra functionality
** This class also handles the creation and addition of objects to the scene, as well
** as handling certain non object-specific updates
*/
class MyScene : 
	public Scene
{
public:
	MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight);
	~MyScene();

	void AddObject(WorldObject* obj);

	/* A Vector of registered lights for objects to check
	** So they can determine which GL_LIGHTs to enable
	*/
	std::vector <LightObject*> *lights; //0x4000 is the starting value of GL_LIGHT0, going up in increments of 1

	XInputController * GetController();
private:
	void Initialise();
	void Projection();
	void Update(const double& deltaTime);
	
	bool checkDistance(float x, float z, float r);

	std::vector<WorldObject*> *objectsList;
	std::vector<double> *angles;

	PlayerObject *player;
	Skybox *skybox;
	SquareObject *flame1;
	SquareObject *flame2;
	LightObject *light2;
	ModelObject *campfire;

	bool flags[2] = { 0, 0 }; // array of flags for interaction with the scene
						   // index	action
						   // -----------------
						   // 0		received interaction
						   // 1		light fire
						   // 2		?

	/* Values used for positioning and scaling objects */
	float z_dist = 200.f;
	float x_dist = -60.f;
	float y_dist = 50.f;

	float building_width = 200.f;
	float building_depth = 300.f;

	XInputController * controller;
};

