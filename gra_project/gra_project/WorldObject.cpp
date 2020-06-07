#include "WorldObject.h"



WorldObject::WorldObject(MyScene* scene, int id, std::string objectName, ColorRGB* color) :
	scene(scene), objectName(objectName), color(color)
{
	newObjects = new std::vector<WorldObject*>;
	light_color = new ColorRGB(1.f, 1.f, 1.f);
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

void WorldObject::setScale(Vertex * size) {
	/* Set original scale */
	this->vSize = size;
	scale[0] = vSize->x;
	scale[1] = vSize->y;
	scale[2] = vSize->z;
}

void WorldObject::setPosition(Vertex * position) {
	/* Set original position */
	this->vPosition = position;
	pos[0] = vPosition->x;
	pos[1] = vPosition->y;
	pos[2] = vPosition->z;

}

void WorldObject::setOrientation(Vertex * orientation) {
	/* Set original orientation */
	this->vOrientation = orientation;
	rotation[0] = vOrientation->x;
	rotation[1] = vOrientation->y;
	rotation[2] = vOrientation->z;
}

void WorldObject::setLightColor(ColorRGB * l_color) {
	this->light_color = l_color;
}

void WorldObject::setColor(ColorRGB * color) {
	this->color = color;
}

void WorldObject::EnableRendering() {
	doRender = true;
}

void WorldObject::DisableRendering() {
	doRender = false;
}

std::string WorldObject::getName() {
	return objectName;
}

std::vector<WorldObject*> * WorldObject::getNewObjects() {
	return newObjects;
}