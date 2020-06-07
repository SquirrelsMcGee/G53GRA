#pragma once
#include "WorldObject.h"

/* This is a class used to draw light sources in the world */
class LightObject :
	public WorldObject
{
public:
	LightObject(MyScene* scene, int id, std::string objectName, ColorRGB *color, int light_id);
	~LightObject();

	void Display();
	void Update(const double& deltaTime);
	std::string animation = "";
private:
	/* These variables are used to define the light characteristics  */
	GLfloat ambient[4] = { 0.f, 0.f, 0.f, 1.f };
	GLfloat diffuse[4] = { 0.f, 0.f, 0.f, 1.f };
	GLfloat specular[4] = { 0.f, 0.f, 0.f, 1.f };

	float light_position[4] = { 0, 0, 0, 1.0f };

	/* The light id is given as an argument to the constructor
	** Since the values from GL_LIGHT0 to GL_LIGHT7 increment by 1
	** I am able to set the light Id by adding a value to GL_LIGHT0
	*/
	int light_id = 0;

	int animation_dir = 1;
};