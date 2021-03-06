#include "FloorTile.h"



FloorTile::FloorTile(MyScene *scene, Vertex * origin, int x, int y, int width, int height)
	: WorldObject(scene, 0, "test", 0),
	scene(scene), xTile(x), yTile(y), xWidth(width), zHeight(height),
	_flagAutospin(false), _flagReset(false), _iKey(false), _jKey(false), _kKey(false),
	_lKey(false), _oKey(false), _uKey(false), _plusKey(false), _minusKey(false),
	_upKey(false), _downKey(false), _leftKey(false), _rightKey(false)
{
	size(_INIT_SIZE);
	this->origin = origin;
}


FloorTile::~FloorTile()
{
}

void FloorTile::Display() {
	glPushMatrix();
	glDisable(GL_LIGHTING);

	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);

	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f); // angle ry about (0,1,0)
	glRotatef(rotation[2], 0.0f, 0.0f, 1.0f); // angle rz about (0,0,1)
	glRotatef(rotation[0], 1.0f, 0.0f, 0.0f); // angle rx about (1,0,0)

	Render();

	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void FloorTile::Update(const double& deltaTime) {
	
	return;
	float velocity = 100.0f*static_cast<float>(deltaTime);
	float shrinkRate = -50.0f*static_cast<float>(deltaTime);

	if (abs(scene->rx) > 10) rotation[1] += scene->rx / 16.f;
	if (abs(scene->ry) > 10) rotation[0] -= scene->ry / 16.f;

	if (abs(scene->lx) > 10) pos[0] += scene->lx / 128.0f;
	if (abs(scene->ly) > 10) pos[2] += scene->ly / 128.0f;

	if (abs(scene->lt) > 10) {
		scale[0] += shrinkRate * scene->lt / 128.0f;
		scale[1] += shrinkRate * scene->lt / 128.0f;
		scale[2] += shrinkRate * scene->lt / 128.0f;
	}

	if (abs(scene->rt) > 10) {
		scale[0] -= shrinkRate * scene->rt / 128.0f;
		scale[1] -= shrinkRate * scene->rt / 128.0f;
		scale[2] -= shrinkRate * scene->rt / 128.0f;
	}

	// Spacebar will reset transformation values
	if (_flagReset)
	{
		//PlaySound(TEXT("naruto.wav"), NULL, SND_FILENAME | SND_ASYNC);
		orientation(0.0f, 0.0f, 0.0f);
		size(_INIT_SIZE);
		position(0.0f, 0.0f, 0.0f);
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


void FloorTile::Render() {
	glBegin(GL_QUADS);
	float xo, yo, zo; // origin points for tile grid
	xo = origin->x;
	yo = origin->y;
	zo = origin->z;

	float x, y, z; // points for each vertex;

	glColor3f(color->x, color->y, color->z);

	// bottom left
	x = xo + (xTile * xWidth);
	y = yo;
	z = zo + (yTile * zHeight) + zHeight;
	glVertex3f(x, y, z);

	//glutSolidSphere(5, 10, 10);

	// bottom right
	x = xo + (xTile * xWidth) + xWidth;
	y = yo;
	z = zo + (yTile * zHeight) + zHeight;
	glVertex3f(x, y, z);

	// top right
	x = xo + (xTile * xWidth) + xWidth;
	y = yo;
	z = zo + (yTile * zHeight);
	glVertex3f(x, y, z);
	
	// top left
	x = xo + (xTile * xWidth);
	y = yo;
	z = zo + (yTile * zHeight);
	glVertex3f(x, y, z);
	glEnd();
}


void FloorTile::HandleKey(unsigned char key, int state, int x, int y)
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

void FloorTile::HandleSpecialKey(int key, int state, int x, int y)
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