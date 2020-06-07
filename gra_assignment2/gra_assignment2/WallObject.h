#pragma once
#include "WorldObject.h"
#include "Functions.h"
#include <array>

class WallObject :
	public WorldObject
{
public:
	WallObject(MyScene* scene, int id, std::string objectName, ColorRGB *color);
	~WallObject();

	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);

private:
	void Render();
	void GenerateQuads();
	
	int xCount = 200;
	int yCount = 50;

	std::vector<Quad*> *quads;
};

