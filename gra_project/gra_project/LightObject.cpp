#include "LightObject.h"

LightObject::LightObject(MyScene* scene, int id, std::string objectName, ColorRGB *color, int light_id)
	: WorldObject(scene, id, objectName, color)
{
	/* Set the light id */
	this->light_id = light_id;
}

LightObject::~LightObject()
{
}


void LightObject::Display() {
	/* This function is used to position and draw the light source in the world */

	if (!doRender) {
		glDisable(GL_LIGHT0 + light_id);
		return;
	}

	/* Set the light position */
	light_position[0] = pos[0];
	light_position[1] = pos[1];
	light_position[2] = pos[2];

	/* Set the colours used by the light */
	ambient[0] = color->x;
	ambient[1] = color->y;
	ambient[2] = color->z;
	diffuse[0] = color->x;
	diffuse[1] = color->y;
	diffuse[2] = color->z;
	specular[0] = color->x;
	specular[1] = color->y;
	specular[2] = color->z;
	
	glPushMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0 + light_id);
	glLightfv(GL_LIGHT0 + light_id, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0 + light_id, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0 + light_id, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0 + light_id, GL_POSITION, light_position);
	glLightf(GL_LIGHT0 + light_id, GL_LINEAR_ATTENUATION, 0.01f);
	glDisable(GL_LIGHTING);
	glPopMatrix();
}

void LightObject::Update(const double & deltaTime) {
	if (animation == "flame") {
		/* Move the light up and down between it's origin and 200 below its origin, 
		** this can be used to simulate dimming of ground lights easily 
		*/
		if (pos[1] < (vPosition->y - 200) || pos[1] > vPosition->y) animation_dir *= -1;
		pos[1] += animation_dir * 2;

		/* Randomly reset the position of the light to give it the flickering affect 
		** that a flame might have 
		*/
		bool flicker = rand() % 64 == 0;
		if (flicker) pos[1] = vPosition->y;
	}
	else {
		/* Other light animations can be added here */
	}
}
