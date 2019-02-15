#include "Triangle.h"

Triangle::Triangle()
{
	// set null pointers
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
	Vertex *defaultColor = new Vertex(0.5f, 0.5f, 0.5f);
	this->c1 = defaultColor;
	this->c2 = defaultColor;
	this->c3 = defaultColor;
}

Triangle::Triangle(Vertex *v1, Vertex *v2, Vertex *v3, Vertex *c1, Vertex *c2, Vertex *c3)
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

void Triangle::setAllColor(Vertex *c) {
	this->c1 = c;
	this->c2 = c;
	this->c3 = c;
}

Triangle::~Triangle()
{
}
