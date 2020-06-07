#pragma once
#include "WorldObject.h"
#include "Functions.h"

class FloorTile :
	public WorldObject
{
public:
	FloorTile(MyScene *scene, Vertex * origin, int x, int y, int width, int height);
	~FloorTile();
	void Display();
	void Update(const double& deltaTime);
	void Render();

	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);

	MyScene * scene;

	// x,y,z coordinate that determines the "top-left" corner
	Vertex * origin;

	// color
	Vertex * color;

	int xWidth = 0;
	int zHeight = 0;

	int xTile = 0; // x and y coordinates for the tile within the grid
	int yTile = 0;

	GLboolean _iKey, _jKey, _kKey, _lKey, _oKey, _uKey;
	GLboolean _plusKey, _minusKey, _upKey, _downKey, _leftKey, _rightKey;
	GLboolean _flagReset, _flagAutospin;

};

