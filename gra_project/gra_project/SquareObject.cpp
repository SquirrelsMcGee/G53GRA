#include "SquareObject.h"



SquareObject::SquareObject(MyScene* scene, int id, std::string objectName, ColorRGB* color, std::string texName, int texCount, float duration) :
	WorldObject(scene, id, objectName, color)
{
	/* Set number of textures to load and the duration of each frame */
	this->texCount = texCount;
	this->duration = duration;

	texids = new std::vector<int>();

	/* Get each texture from the ../Texture/ folder */
	for (int i = 0; i < texCount; i++) {
		texids->push_back(scene->GetTexture("../Texture/" + texName + std::to_string(i) + ".bmp"));
	}
	
}

SquareObject::~SquareObject()
{
}

void SquareObject::Display() {
	/* This fucntion is used to render the object to the screen */

	if (!doRender) return;

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	/* Translate origin of the model, scale and rotate from given values */
	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(rotation[0], 1.0f, 0.0f, 0.0f); // angle rx about (1,0,0)
	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f); // angle ry about (0,1,0)
	glRotatef(rotation[2], 0.0f, 0.0f, 1.0f); // angle rz about (0,0,1)
	glScalef(scale[0], scale[1], scale[2]);
	
	glColor3f(color->x, color->y, color->z);

	/* Bind the current texture */
	glBindTexture(GL_TEXTURE_2D, texids->at(current));

	//  FAR SIDE
	glBegin(GL_QUADS);
	glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
	glVertex3f(1.f, 1.f, -1.f);
	glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
	glVertex3f(-1.f, 1.f, -1.f);
	glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
	glVertex3f(-1.f, 0.f, -1.f);
	glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
	glVertex3f(1.f, 0.f, -1.f);
	glEnd();

	if (renderBothSides) {
		// NEAR SIDE
		glBegin(GL_QUADS);
		glTexCoord2f(1.f, 1.f);  // (u,v) = (1,1)
		glVertex3f(-1.f, 1.f, -1.f);
		glTexCoord2f(0.f, 1.f);  // (u,v) = (0,1)
		glVertex3f(1.f, 1.f, -1.f);
		glTexCoord2f(0.f, 0.f);  // (u,v) = (0,0)
		glVertex3f(1.f, 0.f, -1.f);
		glTexCoord2f(1.f, 0.f);  // (u,v) = (1,0)
		glVertex3f(-1.f, 0.f, -1.f);
		glEnd();
	}

	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void SquareObject::Update(const double& deltaTime) {
	/* This function is called whenever the scene is updated
	** deltaTime refers to the change in time since the previous update
	** I update the timer with the change in time since the last tick
	** If the timer reaches the frame duration, I iterate the current texture
	** index and reset the timer
	*/

	delta += (float)deltaTime;

	if (delta >= duration) {
		current += 1;
		if (current > (texCount - 1)) {
			current = 0;
		}
		delta = 0;
	}
}
