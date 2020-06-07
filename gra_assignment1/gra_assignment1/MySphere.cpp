#include "MySphere.h"

MySphere::MySphere(MyScene *scene) : WorldObject(scene, 0, "test", 0), 
	scene(scene), _flagAutospin(false),
	_flagReset(false), _iKey(false), _jKey(false), _kKey(false),
	_lKey(false), _oKey(false), _uKey(false), _plusKey(false), _minusKey(false),
	_upKey(false), _downKey(false), _leftKey(false), _rightKey(false)
{
	size(_INIT_SIZE);
	CreatePolygons();

	pos[0] = _DEF_X;
	pos[2] = _DEF_Z;
}


MySphere::~MySphere()
{
}

void MySphere::Display() {
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
	//DrawWireframe();

	// Reenable default lighting (IGNORE THIS)
	glEnable(GL_LIGHTING);
	// Revert changes between most recent glPushMatrix and here
	glPopMatrix();
}

void MySphere::DrawAllTriangles() {
	float r, g, b, x, y, z;
	float min = -10.0;
	float max = 10.0;
	
	Triangle *tempT;
	Vertex *tempV;
	Vertex *color;
	Vertex *normal;

	for (size_t i = 0; i < polygons.size(); ++i) {
		glBegin(GL_TRIANGLES);

		tempT = polygons[i];
		normal = CrossProduct(tempT->v1, tempT->v2);
		color = Centroid3(tempT->v1, tempT->v2, tempT->v3);

		tempV = tempT->v1;
		x = tempV->x;
		y = tempV->y;
		z = tempV->z;
		r = FloatNormalise(color->x, min, max);
		g = FloatNormalise(color->y, min, max);
		b = FloatNormalise(color->z, min, max);
		glColor3f(r, g, b);
		glVertex3f(x, y, z);

		tempV = tempT->v2;
		x = tempV->x;
		y = tempV->y;
		z = tempV->z;
		r = FloatNormalise(x, min, max);
		g = FloatNormalise(y, min, max);
		b = FloatNormalise(z, min, max);
		//glColor3f(r, g, b);
		glVertex3f(x, y, z);

		tempV = tempT->v3;
		x = tempV->x;
		y = tempV->y;
		z = tempV->z;
		r = FloatNormalise(x, min, max);
		g = FloatNormalise(y, min, max);
		b = FloatNormalise(z, min, max);
		//glColor3f(r, g, b);
		glVertex3f(x, y, z);
		glEnd();

		/*
		glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(2 * color->x, 2 * color->y, 2 * color->z);
		glVertex3f(0, 0, 0);
		glEnd();
		*/

		delete color;
		delete normal;
	}
	
}

void MySphere::DrawWireframe() {
	float r, g, b, x, y, z;
	float min = -10.0;
	float max = 10.0;

	Triangle *tempT;
	Vertex *tempV;
	glBegin(GL_LINE_LOOP);
	for (size_t i = 0; i < polygons.size(); ++i) {
		tempT = polygons[i];

		tempV = tempT->v1;
		x = tempV->x;
		y = tempV->y;
		z = tempV->z;
		r = 1 - FloatNormalise(x, min, max);
		g = 1 - FloatNormalise(y, min, max);
		b = 1 - FloatNormalise(z, min, max);
		glColor3f(r, g, b);
		glVertex3f(x, y, z);

		tempV = tempT->v2;
		x = tempV->x;
		y = tempV->y;
		z = tempV->z;
		r = 1 - FloatNormalise(x, min, max);
		g = 1 - FloatNormalise(y, min, max);
		b = 1 - FloatNormalise(z, min, max);
		glColor3f(r, g, b);
		glVertex3f(x, y, z);

		tempV = tempT->v3;
		x = tempV->x;
		y = tempV->y;
		z = tempV->z;
		r = 1 - FloatNormalise(x, min, max);
		g = 1 - FloatNormalise(y, min, max);
		b = 1 - FloatNormalise(z, min, max);
		glColor3f(r, g, b);
		glVertex3f(x, y, z);

	}
	glEnd();
}

void MySphere::Subdivide(int count, Triangle *t) {
	if (count == 0) {
		polygons.push_back(t);
		return;
	}
	else {
		Vertex *a, *b, *c, *d, *e, *f;
		Triangle *t1, *t2, *t3, *t4;
		float x1, y1, z1;
		float radius = 10;
		float magnitude = 0;
		
		float min = -20.0;
		float max = 20.0;

		a = t->v1;
		b = t->v2;
		c = t->v3;

		x1 = (a->x + b->x) / 2.0f;
		y1 = (a->y + b->y) / 2.0f;
		z1 = (a->z + b->z) / 2.0f;
		magnitude = sqrt(x1*x1 + y1 * y1 + z1 * z1);
		d = new Vertex(x1 * radius / magnitude, y1 * radius / magnitude, z1 * radius / magnitude);

		x1 = (b->x + c->x) / 2.0f;
		y1 = (b->y + c->y) / 2.0f;
		z1 = (b->z + c->z) / 2.0f;
		magnitude = sqrt(x1*x1 + y1 * y1 + z1 * z1);
		e = new Vertex(x1 * radius / magnitude, y1 * radius / magnitude, z1 * radius / magnitude);
		
		x1 = (a->x + c->x) / 2.0f;
		y1 = (a->y + c->y) / 2.0f;
		z1 = (a->z + c->z) / 2.0f;
		magnitude = sqrt(x1 * x1 + y1 * y1 + z1 * z1);
		f = new Vertex(x1 * radius / magnitude, y1 * radius / magnitude, z1 * radius / magnitude);

		t1 = new Triangle(a, d, f);
		t2 = new Triangle(d, b, e);
		t3 = new Triangle(f, e, c);
		t4 = new Triangle(d, e, f);

		Subdivide(count - 1, t1);
		Subdivide(count - 1, t2);
		Subdivide(count - 1, t3);
		Subdivide(count - 1, t4);
	}
}

void MySphere::CreatePolygons() {

	// Define coordinates for vertices
	float xl = -10;
	float xm = 0;
	float xr = 10;

	float yt = 10;
	float ym = 0;
	float yb = -10;

	float zf = -10;
	float zm = 0;
	float zn = 10;

	// Define vertices using coordinates
	Vertex *vl = new Vertex(xl, ym, zm); // left
	Vertex *vn = new Vertex(xm, ym, zn); // near
	Vertex *vr = new Vertex(xr, ym, zm); // right
	Vertex *vf = new Vertex(xm, ym, zf); // far
	Vertex *tp = new Vertex(xm, yt, zm); // top
	Vertex *bt = new Vertex(xm, yb, zm); // bottom

	// Create triangles from vertices, these 8 triangle objects define an octohedron
	Triangle *ftl = new Triangle(vl, vn, tp); // front top left
	Triangle *ftr = new Triangle(vn, vr, tp); // front top right
	Triangle *btl = new Triangle(vr, vf, tp); // back top left
	Triangle *btr = new Triangle(vf, vl, tp); // back top right

	Triangle *fbl = new Triangle(vn, vl, bt); // front bottom left
	Triangle *fbr = new Triangle(vr, vn, bt); // front bottom right
	Triangle *bbl = new Triangle(vf, vr, bt); // back bottom left
	Triangle *bbr = new Triangle(vl, vf, bt); // back bottom right

	// Subdivide octohedron to make a MySphere
	

	Subdivide(division, ftl);
	Subdivide(division, ftr);
	Subdivide(division, btl);
	Subdivide(division, btr);

	Subdivide(division, fbl);
	Subdivide(division, fbr);
	Subdivide(division, bbl);
	Subdivide(division, bbr);
}

void MySphere::Update(const double& deltaTime) {
	float velocity = 100.0f*static_cast<float>(deltaTime);
	float shrinkRate = -50.0f*static_cast<float>(deltaTime);

	// Spacebar will reset transformation values
	if (_flagReset)
	{
		orientation(0.0f, 0.0f, 0.0f);
		size(_INIT_SIZE);
		position(_DEF_X, 0.0f, _DEF_Z);
		_flagReset = false;
	}

	/*
	If keys pressed down:
	[u][i][o]
	[j][k][l]

	rotate around x,y,z axes for (i,k), (j,l) and (u,o) respectively
	*/

	if (_flagAutospin) {
		rotation[0] -= velocity;
		rotation[1] -= velocity;
	}

	// 'i' pressed down, decrease rotation around 'x'
	if (_iKey) rotation[0] -= velocity;
	// 'j' pressed down, decrease rotation around 'y'
	if (_jKey) rotation[1] -= velocity;
	// 'k' pressed down, increase rotation around 'x'
	if (_kKey) rotation[0] += velocity;
	// 'l' pressed down, increase rotation around 'y'
	if (_lKey) rotation[1] += velocity;
	// 'o' pressed down, decrease rotation around 'z'
	if (_oKey) rotation[2] -= velocity;
	// 'u' pressed down, increase rotation around 'x'
	if (_uKey) rotation[2] += velocity;

	/*
	If keys pressed down:
	[-]
	|+|  or   [-]^[+]
	|_|
	scale by all x,y,z axes equally, + to grow, - to shrink
	*/
	// '-' pressed down (and no scale value is below 1.0)
	if (_minusKey && scale[0] > 1.0f && scale[1] > 1.0f && scale[2] > 1.0f)
	{
		// increase shrinkage by constant (negative) rate
		scale[0] += shrinkRate;
		scale[1] += shrinkRate;
		scale[2] += shrinkRate;
	}
	// '+' pressed down
	if (_plusKey)
	{
		// decrease shrinkage (e.g. grow)
		scale[0] -= shrinkRate;
		scale[1] -= shrinkRate;
		scale[2] -= shrinkRate;
	}

	/*
	If keys pressed down:
	[/\]
	[<-][\/][->]
	translate along x and y axes, for (left, right) and (up, down) respectively
	*/
	if (_upKey) pos[1] += velocity;
	if (_downKey) pos[1] -= velocity;
	if (_leftKey) pos[0] -= velocity;
	if (_rightKey) pos[0] += velocity;
}


void MySphere::HandleKey(unsigned char key, int state, int x, int y)
{
	/*
	This function is called continuously when a key is pressed AND when
	it is released. The variable 'key' describes the character or the key,
	e.g. for the a key, key == 'a'. Variable 'state' describes whether the
	key has been pressed or released. While the key is pressed, state = 1,
	when released, the function is called with state = 0. x and y describe
	position of the mouse at callback (this can be ignored for now).
	*/

	// Switch on key char
	// Set flag for control keys, (i,j,k,l,o,u,+,-,space) to state value
	// i.e. if 'i' is pressed, _iKey = true, if 'i' released, _iKey = false
	switch (key)
	{
	case 'i':
		_iKey = static_cast<GLboolean>(state);
		break;
	case 'j':
		_jKey = static_cast<GLboolean>(state);
		break;
	case 'k':
		_kKey = static_cast<GLboolean>(state);
		break;
	case 'l':
		_lKey = static_cast<GLboolean>(state);
		break;
	case 'o':
		_oKey = static_cast<GLboolean>(state);
		break;
	case 'u':
		_uKey = static_cast<GLboolean>(state);
		break;
	case '+': // with shift
	case '=': // without shift
		_plusKey = static_cast<GLboolean>(state);
		break;
	case '-':
		_minusKey = static_cast<GLboolean>(state);
		break;
	case ' ':
		_flagReset = true;
		break;
	case 'f':
		if (state == 0) {
			_flagAutospin = !_flagAutospin;
			break;
		}
	}
}

void MySphere::HandleSpecialKey(int key, int state, int x, int y)
{
	/*
	This function is called continuously when a special key is pressed
	AND when it is released. The variable 'key' describes the keycode
	for the key, e.g. for the UP key, key == 0x0065 (or GLUT_KEY_UP).
	Variable 'state' describes whether the key has been pressed or
	released. While the key is pressed, state = 1, when released, the
	function is called with state = 0. x and y describe position of the
	mouse at callback.
	See the Lab 4 for details on special keys.
	*/

	// Switch on key code (using GLUT #defines)
	// Set flag for control keys, (up, down, left, right) to state value
	// i.e. if 'up' is pressed, _upKey = true, if 'up' released, _upKey = false
	switch (key)
	{
	case GLUT_KEY_UP:
		_upKey = static_cast<GLboolean>(state);
		break;
	case GLUT_KEY_DOWN:
		_downKey = static_cast<GLboolean>(state);
		break;
	case GLUT_KEY_LEFT:
		_leftKey = static_cast<GLboolean>(state);
		break;
	case GLUT_KEY_RIGHT:
		_rightKey = static_cast<GLboolean>(state);
		break;
	}
}