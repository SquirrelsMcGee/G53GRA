#include "WallObject.h"



WallObject::WallObject(MyScene* scene, int id, std::string objectName, ColorRGB *color, Vertex* origin, bool square, std::string texName) : WorldObject(scene, id, objectName, color)
{
	quads = new std::vector<Quad*>;
	position(origin->x, origin->y, origin->z);

	/* If this value is true, then make the wall a square rather than a 
	** rectangle
	*/
	if (square) {
		yCount = xCount;
	}

	/* Get the texture */
	textureId = scene->GetTexture("../Texture/" + texName + ".bmp");

	/* Generate the faces */
	GenerateQuads();
}


WallObject::~WallObject()
{
}

void WallObject::Display() {
	/* This function is used to initialise rendering to the screen */

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	/* Enable all the lights that are currently registered in MyScene */
	for (size_t i = 0; i < scene->lights->size(); ++i) {
		glEnable(GL_LIGHT0 + (int)i);
	}

	/* Translate origin of the model, scale and rotate from given values */
	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);
	glRotatef(rotation[0], 1.0f, 0.0f, 0.0f); // angle rx about (1,0,0)
	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f); // angle ry about (0,1,0)
	glRotatef(rotation[2], 0.0f, 0.0f, 1.0f); // angle rz about (0,0,1)
	
	glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes
	glBindTexture(GL_TEXTURE_2D, textureId);

	glBegin(GL_QUADS);
	Render();
	glEnd();

	glBindTexture(GL_TEXTURE_2D, NULL);

	glPopAttrib();
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	if (!lightModel) return;
	
	float zdist = 10.0f;

	glPushMatrix();
	glTranslatef(pos[0], pos[1] + 5.f, pos[2] + zdist);
	glScalef(1.0, 10.0, 1.0);
	glColor3f(0.1f, 0.1f, 0.1f);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(pos[0], pos[1] + 10.0f, pos[2] + zdist - 5.0f);
	glScalef(1.0, 1.0, 10.0);
	glColor3f(0.1f, 0.1f, 0.1f);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2] + zdist);
	glScalef(2.0, 2.0f, 2.0f);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(2, 8, 8);
	glPopMatrix();
}

void WallObject::Render() {

	/* Update ambient and diffuse light attributes from given value */
	mat_ambient[0] = color->x;
	mat_ambient[1] = color->y;
	mat_ambient[2] = color->z;
	mat_diffuse[0] = color->x;
	mat_diffuse[1] = color->y;
	mat_diffuse[2] = color->z;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


	/* Set wall colour and transparency value */
	glColor3f(color->x, color->y, color->z);
	glColor4f(color->x, color->y, color->z, alpha);

	glNormal3f(0.0, 0.0, 1.0f);

	/* These variables used as temporary pointers */
	Quad *q; // face
	Vertex *v, *t; // vertex and texture coordinate

	for (size_t i = 0; i < quads->size(); i+=1) {
		/* Set texture coordinates and place vertices for every face */
		q = quads->at(i);

		v = q->v1;
		t = q->c1;
		glTexCoord2f(t->x, t->y);
		glVertex3f(v->x, v->y, v->z);
		
		v = q->v2;
		t = q->c2;
		glTexCoord2f(t->x, t->y);
		glVertex3f(v->x, v->y, v->z);
		
		v = q->v3;
		t = q->c3;
		glTexCoord2f(t->x, t->y);
		glVertex3f(v->x, v->y, v->z);
		
		v = q->v4;
		t = q->c4;
		glTexCoord2f(t->x, t->y);
		glVertex3f(v->x, v->y, v->z);
	}
}

void WallObject::GenerateQuads() {
	/* This function generates quad faces with texture coordinates */
	float x, y, z, w;
	z = 0; // z depth
	w = 10; // face width

	x = -(xCount * w / 2.0f); // x offset
	y = -(yCount * w / 2.0f); // y offset
	

	float tw = 1.0f / (float) xCount; // texture segment width
	float th = 1.0f / (float) yCount; // texture segment height

	for (int i = 0; i < xCount; i++) {
		for (int j = 0; j < yCount; j++) {

			/* x, y coodinates of the quad, and texture coordinates for it also */
			float x1 = x + (i * w);
			float y1 = y + (j * w);
			float tx1 = i * tw;
			float ty1 = (j * th);

			/* Create face */
			Quad* q = new Quad(
				new Vertex(x1, y1, z),
				new Vertex(x1, y1 - w, z),
				new Vertex(x1 + w, y1 - w, z),
				new Vertex(x1 + w, y1, z)
			);

			/* Here I'm using the colour values for texture coordinates 
			** As otherwise these values wouldn't be used
			** So why not use them for this
			*/
			q->c1 = new ColorRGB(tx1, (ty1 + th), 0);
			q->c2 = new ColorRGB(tx1, (ty1), 0);
			q->c3 = new ColorRGB(tx1 + tw, (ty1), 0);
			q->c4 = new ColorRGB(tx1 + tw, (ty1 + th), 0);

			quads->push_back(q);
		}
	}
}