#pragma once

#include <vector>
#include <stdio.h>
#include <iostream>

#include "Functions.h"
#include "MyScene.h"

/* This class is used as a super-class for all other renderables 
** It is an extension of DisplayableObject and includes methods and attributes
** that are not included in DisplayableObject
*/
class WorldObject : 
	public DisplayableObject,
	public Animation,
	public Input
{
public:
	WorldObject(MyScene* scene, int id, std::string objectName, ColorRGB* color);
	~WorldObject();

	/* Overridden from DisplayableObject */
	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);

	/* Extra methods, allows external manipulation of internal class attributes */
	void setScale(Vertex * size);
	void setPosition(Vertex * position);
	void setOrientation(Vertex * orientation);
	void setLightColor(ColorRGB * l_color);
	void setColor(ColorRGB * color);
	void EnableRendering();
	void DisableRendering();

	/* Used to get the Object class*/
	std::string getName();

	/* Used to check if an object wants to generate new Renderables */
	std::vector<WorldObject*> * getNewObjects();
	std::vector<WorldObject*> * newObjects;

protected:
	/* Values used by subclasses */
	MyScene* scene; // reference to MyScene
	int id; 
	std::string objectName; // Object class name
	ColorRGB* color; // Polygon colour
	ColorRGB* light_color; // light ambient and diffuse colours

	/* Used as a origin position for reset, and other calculations */
	Vertex * vSize;
	Vertex * vPosition;
	Vertex * vOrientation;

	bool doRender = true;

};

