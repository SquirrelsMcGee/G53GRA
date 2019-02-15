#include "WorldObject.h"



WorldObject::WorldObject(MyScene *scene, int id, string type, int colour) : 
	scene(scene), _flagAutospin(false), _flagReset(false), _iKey(false), _jKey(false), _kKey(false),
	_lKey(false), _oKey(false), _uKey(false), _plusKey(false), _minusKey(false),
	_upKey(false), _downKey(false), _leftKey(false), _rightKey(false)
{
	// Default world object
	newObjs = new vector<WorldObject*>;
}
/*
WorldObject::WorldObject(MyScene *scene, int id, string type, int colour, WorldObject *parent) :
	scene(scene), _flagAutospin(false), _flagReset(false), _iKey(false), _jKey(false), _kKey(false),
	_lKey(false), _oKey(false), _uKey(false), _plusKey(false), _minusKey(false),
	_upKey(false), _downKey(false), _leftKey(false), _rightKey(false)
{
	// World object that has a parent object
}*/

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