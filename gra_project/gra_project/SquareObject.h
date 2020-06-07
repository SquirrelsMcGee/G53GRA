#pragma once
#include "WorldObject.h"
#include "Functions.h"

/* This is a class that is used to render a square to the scene
** This supports animated textures by loading multiple *.bmp files
*/
class SquareObject :
	public WorldObject
{
public:
	SquareObject(MyScene* scene, int id, std::string objectName, ColorRGB* color, std::string texPath, int texCount, float duration);
	~SquareObject();

	void Display();
	void Update(const double& deltaTime);

	/* This renders the plane so it faces both ways */
	bool renderBothSides = false;

private:
	/* These variables are used for animated textures */
	int texCount = 0; // number of textures
	int current = 0;  // current texture index
	std::vector<int> *texids; // vector of texture ids

	/* These variables are used to keep track of time for texture updates */
	float duration = 0; // amount of time until next texture update
	float delta = 0;	// current change in time since last texture update

	
};

