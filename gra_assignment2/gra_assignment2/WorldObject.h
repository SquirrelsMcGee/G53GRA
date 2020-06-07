#pragma once

#include <vector>
#include <stdio.h>
#include <iostream>

#include "Functions.h"
#include "MyScene.h"
#include "Triangle.h"


class WorldObject : 
	public DisplayableObject,
	public Animation,
	public Input

{
public:
	WorldObject(MyScene* scene, int id, std::string objectName, ColorRGB* color);
	~WorldObject();

	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);
	std::string getName();
	std::vector<WorldObject*> * getNewObjects();
	
	std::vector<WorldObject*> * newObjects;

protected:
	MyScene* scene;
	int id;
	std::string objectName;
	ColorRGB* color;
};

