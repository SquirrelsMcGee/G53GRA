#pragma once
#include "WorldObject.h"

/* This is a class that is used to render a skybox onto the scene to act
** as a background
*/
class Skybox :
	public WorldObject
{
public:
	Skybox(MyScene* scene, int id, std::string objectName, ColorRGB* color);
	~Skybox();

	void Display();

	/* Skybox textures should be found in "../Texture/skybox/
	** and be named f0.bmp to f5.bmp
	*/
	int texids[6] = { 0, 0, 0, 0, 0, 0 };
};

