#include "WallObject.h"



WallObject::WallObject(MyScene* scene, int id, std::string objectName, ColorRGB *color) : WorldObject(scene, id, objectName, color)
{
	newObjects = new std::vector<WorldObject*>;
	quads = new std::vector<Quad*>;

	GenerateQuads();
}


WallObject::~WallObject()
{
}

void WallObject::Display() {

	float zdist = 10.0f;
	float colorMult = 1.0f;
	float ambient[] = { 1.0f, 1.0f, 0.9f, 1.0f };
	float diffuse[] = { 1.0f, 1.0f, 0.9f, 1.0f };
	float specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float light_position[] = { 0.0f, 0.0f, zdist, 1.0f };


	glPushMatrix();

	glEnable(GL_LIGHTING);
	
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	float spot_direction[] = { 0.0, 0.0, -1.0 };
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0f);
	//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 120.0f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1f);

	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);

	glRotatef(rotation[0], 0.0f, 0.0f, 0.0f); // angle rx about (1,0,0)
	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f); // angle ry about (0,1,0)
	glRotatef(rotation[2], 0.0f, 0.0f, 1.0f); // angle rz about (0,0,1)
	
	glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes

	glBegin(GL_QUADS);
	Render();
	glEnd();

	glPopAttrib();

	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 8.0, zdist);
	glScalef(1.0, 10.0, 1.0);
	glColor3f(0.1, 0.1, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 10.0, zdist - 5.0);
	glScalef(1.0, 1.0, 10.0);
	glColor3f(0.1, 0.1, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, zdist);
	glScalef(2.0, 2.0f, 2.0f);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(2, 8, 8);
	glPopMatrix();
}

void WallObject::Render() {
	float mat_ambient[] = { color->x, color->y, color->z, 1.0f };
	float mat_diffuse[] = { color->x, color->y, color->z, 1.0f };
	float mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float mat_shininess[] = { 48.0 }; // 0-128

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	Quad * q;
	Vertex *v;
	glColor3f(color->x, color->y, color->z);

	
	glNormal3f(0.0, 0.0, 1.0f);

	for (size_t i = 0; i < quads->size(); ++i) {
		q = quads->at(i);
		v = q->v1;
		glVertex3f(v->x, v->y, v->z);
		
		v = q->v2;
		glVertex3f(v->x, v->y, v->z);

		v = q->v3;
		glVertex3f(v->x, v->y, v->z);

		v = q->v4;
		glVertex3f(v->x, v->y, v->z);

	}
}

void WallObject::GenerateQuads() {
	float x, y, z, w;
	x = -(xCount / 2.0f);
	y = -(yCount / 2.0f);
	z = 1;
	w = 2;
	for (int i = 0; i < xCount; i++) {
		for (int j = 0; j < yCount; j++) {
			quads->push_back(new Quad(
				new Vertex(x + i, y + j, z),
				new Vertex(x + i, y + (j - w), z),
				new Vertex(x + (i + w), y+ (j - w), z),
				new Vertex(x + (i + w), y + j, z)
			));
		}
	}
}

void WallObject::Update(const double& deltaTime) { /* Stub */ return; }
void WallObject::HandleKey(unsigned char key, int state, int x, int y) { /* Stub */ return; }
void WallObject::HandleSpecialKey(int key, int state, int x, int y) { /* Stub */ return; }