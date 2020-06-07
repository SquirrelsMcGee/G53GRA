#pragma once
#include "WorldObject.h"
#include "Functions.h"
#include <array>

/* This class is used to draw a wall made of segmented Quad faces 
** The reason this is done is so the lighting doesn't light the entire wall
** which would happen if it was just made of 4 vertices
*/
class WallObject :
	public WorldObject
{
public:
	WallObject(MyScene* scene, int id, std::string objectName, ColorRGB *color, Vertex* origin, bool square, std::string texName);
	~WallObject();

	void Display();

	bool lightModel = false; // Used to draw a lantern on the wall

	bool square = false; // used to make the wall a square rather than a rectangle
	float alpha = 1.0f;  // used to make the wall transparent

private:
	void Render(); // renders the wall
	void GenerateQuads(); // creates the quad faces
	
	int xCount = 30; // number of quads horizontally
	int yCount = 20; // number of quads vertically

	std::vector<Quad*> *quads; // vector of faces

	int textureId; // texture for the wall

	/* These variables are used to define the light characteristics of the model */
	GLfloat mat_ambient[4] = { 0.f, 0.f, 0.f, 1.f };
	GLfloat mat_diffuse[4] = { 0.f, 0.f, 0.f, 1.f };
	GLfloat mat_specular[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
	GLfloat mat_shininess[1] = { 65.f }; // 0-128

};

