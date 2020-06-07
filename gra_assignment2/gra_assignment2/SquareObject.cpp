#include "SquareObject.h"



SquareObject::SquareObject(MyScene* scene, int id, std::string objectName, ColorRGB* color) :
	WorldObject(scene, id, objectName, color)
{
	quad = new Quad(v1, v2, v3, v4);
	quad->setAllColor(color);
	theta = (360.0f / scene->squareCount) * id;
	scene->AddAngle(theta);

	texId = scene->GetTexture("Texture/12.bmp");
	tcX = 0.1f * id;

	newObjects = new std::vector<WorldObject*>;
}


SquareObject::~SquareObject()
{
}


void SquareObject::Display() {
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texId);

	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0] * 10.f, scale[1] * 10.f, scale[2] * 10.f);

	glRotatef(rotation[0], 0.0f, 0.0f, 0.0f); // angle rx about (1,0,0)
	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f); // angle ry about (0,1,0)
	glRotatef(rotation[2], 0.0f, 0.0f, 1.0f); // angle rz about (0,0,1)
	
	glFrontFace(GL_CCW);
	glBegin(GL_QUADS);
	
	quad->tcX = tcX;
	quad->tcY = tcY;
	quad->Render();
	glTexCoord1f(tcX + 0.5f);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void SquareObject::Update(const double& deltaTime) {
	
	if (!spin) return;

	/* Rotates in a circle and translates about [x=cos(theta), y=sin(theta)] where theta is an angle in radians */

	float radius = 10.0f;
	float halfWidth = 1.0f;
	float angle = 1.0f;
	

	rotation[2] = theta;

	// Calculate the new point to rotate the whole object around
	pos[0] = ((float) cos(theta * PI/180.0f)) * 100.0f;
	pos[1] = ((float) sin(theta * PI/180.0f)) * 100.0f;

	theta += angle; // multiply by the desired speed
	if (theta > 360.0f) {
		theta = 0.0f;
	}

	if (_flagNew && false == true) {
		SquareObject* square = new SquareObject(scene, 100, "SquareObject", new ColorRGB(1, 1, 1));
		square->scale[0] = 10.0f;
		square->scale[1] = 10.0f;

		newObjects->push_back(square);
		_flagNew = false;
	}
}

void SquareObject::HandleKey(unsigned char key, int state, int x, int y) {
	//if (state == 1) return;
	
	if (key >= 48 || key <= 57) {
		float k = (key - 48.0f);

		std::cout << key << std::endl;

		tcX = 0.1f * k;

		quad->tcX = tcX;
		quad->tcY = tcY;
	}
	if (id != 0) return;
	if (key == 'n') {
		_flagNew = true;
	}
}

void SquareObject::HandleSpecialKey(int key, int state, int x, int y) {
}