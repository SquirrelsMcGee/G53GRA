#include "Triangle.h"

Triangle::Triangle()
{
	// set null pointers as default
	this->v1 = nullptr;
	this->v2 = nullptr;
	this->v3 = nullptr;

	this->c1 = nullptr;
	this->c2 = nullptr;
	this->c3 = nullptr;
}

Triangle::Triangle(Vertex *v1, Vertex *v2, Vertex *v3)
{
	// set coordinates
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;

	// set default colour
	ColorRGB *defaultColor = new ColorRGB(0.5f, 0.5f, 0.5f);
	this->c1 = defaultColor;
	this->c2 = defaultColor;
	this->c3 = defaultColor;
}

Triangle::Triangle(Vertex *v1, Vertex *v2, Vertex *v3, ColorRGB *c1, ColorRGB *c2, ColorRGB *c3)
{
	// set coordinates
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	// set colours
	this->c1 = c1;
	this->c2 = c2;
	this->c3 = c3;
}

Triangle::~Triangle()
{
}

void Triangle::Render() {

	if (c1 != nullptr) glColor3f(c1->x, c1->y, c1->z);
	if (v1 != nullptr) glVertex3f(v1->x, v1->y, v1->z);

	if (c2 != nullptr) glColor3f(c2->x, c2->y, c2->z);
	if (v2 != nullptr) glVertex3f(v2->x, v2->y, v2->z);

	if (c3 != nullptr) glColor3f(c3->x, c3->y, c3->z);
	if (v3 != nullptr) glVertex3f(v3->x, v3->y, v3->z);
}

void Triangle::setAllColor(ColorRGB *c) {
	this->c1 = c;
	this->c2 = c;
	this->c3 = c;
}

