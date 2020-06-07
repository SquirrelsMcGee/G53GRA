#include "Quad.h"

Quad::Quad()
{
	/* Set Vertex points as null pointers by default */
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
	/* Set all Vertex points */
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->v4 = v4;

	/* Set default colour */
	ColorRGB *defaultColor = new ColorRGB(0.5f, 0.5f, 0.5f);
	this->c1 = defaultColor;
	this->c2 = defaultColor;
	this->c3 = defaultColor;

	winding = GL_CCW;
}

Quad::Quad(Vertex *v1, Vertex *v2, Vertex *v3, Vertex *v4, ColorRGB *c1, ColorRGB *c2, ColorRGB *c3, ColorRGB *c4)
{
	/* Set all Vertex points */
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;

	/* Set all colours */
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
	/* This method is called in order to render the Quad to the screen
	** Ensure that the required glBegin command has already been called 
	** before calling this function
	** Texture coordinates and colours for each Vertex point are provided
	*/
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
}


void Quad::setAllColor(ColorRGB *c) {
	/* This function is used to set the colour of all the Vertex points as the same */
	this->c1 = c;
	this->c2 = c;
	this->c3 = c;
	this->c4 = c;
}

void Quad::PrintC() {
	/* This function is used as a debugging tool to print colour values to the console */
	std::cout << "c1:" << c1->x << "," << c1->y << "," << c1->z << " ";
	std::cout << "c2:" << c2->x << "," << c2->y << "," << c1->z << " ";
	std::cout << "c3:" << c3->x << "," << c3->y << "," << c3->z << " ";
	std::cout << "c4:" << c4->x << "," << c4->y << "," << c4->z << " ";
	std::cout << std::endl;
}

void Quad::PrintV() {
	/* This function is used as a debugging tool to print Vertex point values to the console */
	std::cout << "v1:" << v1->x << "," << v1->y << "," << v1->z << " ";
	std::cout << "v2:" << v2->x << "," << v2->y << "," << v2->z << " ";
	std::cout << "v3:" << v3->x << "," << v3->y << "," << v3->z << " ";
	std::cout << "v4:" << v4->x << "," << v4->y << "," << v4->z << " ";
	std::cout << std::endl;
}
