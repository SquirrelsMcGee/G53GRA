#include "Triangle.h"

Triangle::Triangle()
{
	/* Set Vertex points as null pointers by default */
	this->v1 = nullptr;
	this->v2 = nullptr;
	this->v3 = nullptr;

	this->c1 = nullptr;
	this->c2 = nullptr;
	this->c3 = nullptr;
}

Triangle::Triangle(Vertex *v1, Vertex *v2, Vertex *v3)
{
	/* Set all Vertex points */
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;

	/* Set default colour */
	ColorRGB *defaultColor = new ColorRGB(0.5f, 0.5f, 0.5f);
	this->c1 = defaultColor;
	this->c2 = defaultColor;
	this->c3 = defaultColor;
}

Triangle::Triangle(Vertex *v1, Vertex *v2, Vertex *v3, ColorRGB *c1, ColorRGB *c2, ColorRGB *c3)
{
	/* Set all Vertex points */
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;

	/* Set all colours */
	this->c1 = c1;
	this->c2 = c2;
	this->c3 = c3;
}

Triangle::~Triangle()
{
}

void Triangle::Render() {
	/* This method is called in order to render the Triangle to the screen
	** Ensure that the required glBegin command has already been called
	** before calling this function
	** Colours for each Vertex point are provided
	*/
	if (c1 != nullptr) glColor3f(c1->x, c1->y, c1->z);
	if (v1 != nullptr) glVertex3f(v1->x, v1->y, v1->z);

	if (c2 != nullptr) glColor3f(c2->x, c2->y, c2->z);
	if (v2 != nullptr) glVertex3f(v2->x, v2->y, v2->z);

	if (c3 != nullptr) glColor3f(c3->x, c3->y, c3->z);
	if (v3 != nullptr) glVertex3f(v3->x, v3->y, v3->z);
}

void Triangle::setAllColor(ColorRGB *c) {
	/* This function is used to set the colour of all the Vertex points as the same */
	this->c1 = c;
	this->c2 = c;
	this->c3 = c;
}

