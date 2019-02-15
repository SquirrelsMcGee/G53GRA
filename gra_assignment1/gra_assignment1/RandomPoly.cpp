#include "RandomPoly.h"



RandomPoly::RandomPoly()
{
	size(_INIT_SIZE);
}


RandomPoly::~RandomPoly()
{
}

void RandomPoly::DrawAllTriangles() {
	float x, y, z, r, g, b;
	Triangle *tempT;
	Vertex *tempV;
	//Vertex *color;
	glBegin(GL_TRIANGLES);
	for (size_t i = 0; i < polygons.size(); ++i) {
		tempT = polygons[i];

		tempV = tempT->v1;
		x = tempV->x;
		y = tempV->y;
		z = tempV->z;
		r = tempT->c1->x;
		g = tempT->c1->y;
		b = tempT->c1->z;
		glColor3f(r, g, b);
		glVertex3f(x, y, z);

		tempV = tempT->v2;
		x = tempV->x;
		y = tempV->y;
		z = tempV->z;
		r = tempT->c2->x;
		g = tempT->c2->y;
		b = tempT->c2->z;
		glColor3f(r, g, b);
		glVertex3f(x, y, z);

		tempV = tempT->v3;
		x = tempV->x;
		y = tempV->y;
		z = tempV->z;
		r = tempT->c3->x;
		g = tempT->c3->y;
		b = tempT->c3->z;
		glColor3f(r, g, b);
		glVertex3f(x, y, z);

		//delete color;
	}
	glEnd();
}

void RandomPoly::CreateRandom() {
	int range = 10;
	float offset = -5.0;

	for (int i = 0; i < 50; i++) {
		polygons.push_back(
			new Triangle(
				new Vertex((rand() % range) + offset, (rand() % range) + offset, (rand() % range) + offset - 10),
				new Vertex((rand() % range) + offset, (rand() % range) + offset, (rand() % range) + offset - 10),
				new Vertex((rand() % range) + offset, (rand() % range) + offset, (rand() % range) + offset - 10),
				new Vertex((rand() % 255) / 255.0, (rand() % 255) / 255.0, (rand() % 255) / 255.0),
				new Vertex((rand() % 255) / 255.0, (rand() % 255) / 255.0, (rand() % 255) / 255.0),
				new Vertex((rand() % 255) / 255.0, (rand() % 255) / 255.0, (rand() % 255) / 255.0)));
	}
}

void RandomPoly::Display() {
	// Push the current transformation matrix.
	// for now just put it at the start and end of each draw call you make
	glPushMatrix();

	// Disable default lighting effects (IGNORE THIS)
	glDisable(GL_LIGHTING);

	// Translate object into its position first

	glTranslatef(pos[0], pos[1], pos[2]);

	// Scale object (but not translation) by calling scale after translate
	glScalef(scale[0], scale[1], scale[2]);

	// Rotate object in new position, in order y>z>x axes
	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f); // angle ry about (0,1,0)
	glRotatef(rotation[2], 0.0f, 0.0f, 1.0f); // angle rz about (0,0,1)
	glRotatef(rotation[0], 1.0f, 0.0f, 0.0f); // angle rx about (1,0,0)

											  // Local function to draw coloured cube
	DrawAllTriangles();

	// Reenable default lighting (IGNORE THIS)
	glEnable(GL_LIGHTING);
	// Revert changes between most recent glPushMatrix and here
	glPopMatrix();
}


void RandomPoly::Update(const double& deltaTime) {
	
}
