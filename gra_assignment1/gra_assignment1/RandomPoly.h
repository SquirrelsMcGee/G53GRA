#pragma once
#include <vector>

#include "Framework\Interface\DisplayableObject.h"
#include "Framework\Interface\Animation.h"
#include "Framework\Interface\Input.h"

#include "Triangle.h"
#include "Functions.h"

using namespace std;

class RandomPoly :
	public DisplayableObject,
	public Animation,
	public Input
{
public:
	RandomPoly();
	~RandomPoly();
	void Display();
	void Update(const double& deltaTime);
	//void HandleKey(unsigned char key, int state, int x, int y);
	//void HandleSpecialKey(int key, int state, int x, int y);

private:
	void DrawAllTriangles();
	//void Subdivide(int count, Triangle *t);
	void CreateRandom();

	vector<Triangle*> polygons;

	GLboolean _iKey, _jKey, _kKey, _lKey, _oKey, _uKey;
	GLboolean _plusKey, _minusKey, _upKey, _downKey, _leftKey, _rightKey;
	GLboolean _flagReset;
};