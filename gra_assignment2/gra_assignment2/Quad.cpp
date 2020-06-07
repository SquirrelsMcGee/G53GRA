#include "Quad.h"

Quad::Quad()
{
	// set null pointers as default
	this->v1 = nullptr;
	this->v2 = nullptr;
	this->v3 = nullptr;
	this->v4 = nullptr;

	this->c1 = nullptr;
	this->c2 = nullptr;
	this->c3 = nullptr;

	winding = GL_CCW;
}

Quad::Quad(Vertex *v1, Vertex *v2, Vertex *v3, Vertex *v4)
{
	// set coordinates
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->v4 = v4;

	// set default colour
	Vertex *defaultColor = new Vertex(0.5f, 0.5f, 0.5f);
	this->c1 = defaultColor;
	this->c2 = defaultColor;
	this->c3 = defaultColor;

	winding = GL_CCW;
}

Quad::Quad(Vertex *v1, Vertex *v2, Vertex *v3, Vertex *v4, ColorRGB *c1, ColorRGB *c2, ColorRGB *c3, ColorRGB *c4)
{
	// set coordinates
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;

	// set colours from given colour values
	this->c1 = c1;
	this->c2 = c2;
	this->c3 = c3;
	this->c4 = c4;

	winding = GL_CCW;
}

Quad::~Quad()
{
}

void Quad::Render() {

	if (tcX != -1) glTexCoord2f(tcX, 1.0f);
	if (c1 != nullptr) glColor3f(c1->x, c1->y, c1->z);
	if (v1 != nullptr) glVertex3f(v1->x, v1->y, v1->z);
	
	if (tcX != -1) glTexCoord2f(tcX, 0.0f);
	if (c2 != nullptr) glColor3f(c2->x, c2->y, c2->z);
	if (v2 != nullptr) glVertex3f(v2->x, v2->y, v2->z);
	
	if (tcX != -1) glTexCoord2f(tcX + 0.1f, 0.0f);
	if (c3 != nullptr) glColor3f(c3->x, c3->y, c3->z);
	if (v3 != nullptr) glVertex3f(v3->x, v3->y, v3->z);
	
	if (tcX != -1) glTexCoord2f(tcX + 0.1f, 1.0f);
	if (c4 != nullptr) glColor3f(c4->x, c4->y, c4->z);
	if (v4 != nullptr) glVertex3f(v4->x, v4->y, v4->z);
	

	//glEnd();
}

void Quad::setAllColor(Vertex *c) {
	this->c1 = c;
	this->c2 = c;
	this->c3 = c;
	this->c4 = c;
}

