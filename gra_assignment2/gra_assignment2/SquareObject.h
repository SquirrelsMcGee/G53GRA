#pragma once
#include "WorldObject.h"
#include "Functions.h"

class SquareObject :
	public WorldObject
{
public:
	SquareObject(MyScene* scene, int id, std::string objectName, ColorRGB* color);
	~SquareObject();

	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);



	//void Render();
	bool spin = true;

private:
	Quad* quad;

	Vertex* v1 = new Vertex(-1, 1, 0);
	Vertex* v2 = new Vertex(-1, -1, 0);
	Vertex* v3 = new Vertex(1, -1, 0);
	Vertex* v4 = new Vertex(1, 1, 0);

	float theta = 0.0f + rand() % 360;
	
	GLfloat xRot = 0.0f;
	GLfloat yRot = 0.0f;
	GLfloat zRot = 0.0f;

	int texId;
	float tcX = 0.0f;
	float tcY = 0.0f;

	GLboolean _flagNew = false;
};

