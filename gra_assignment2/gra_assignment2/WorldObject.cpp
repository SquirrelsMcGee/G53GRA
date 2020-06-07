#include "WorldObject.h"



WorldObject::WorldObject(MyScene* scene, int id, std::string objectName, ColorRGB* color) :
	scene(scene), objectName(objectName), color(color)
{
}


WorldObject::~WorldObject()
{
}


void WorldObject::Display() {
	// Default display behaviour
}

void WorldObject::Update(const double& deltaTime) {
	// Default update behaviour
}

void WorldObject::HandleKey(unsigned char key, int state, int x, int y) {
	// Default key handle behaviour
}

void WorldObject::HandleSpecialKey(int key, int state, int x, int y) {
	// Default special key handle behavior
}

std::string WorldObject::getName() {
	return objectName;
}

std::vector<WorldObject*> * WorldObject::getNewObjects() {
	return newObjects;
}