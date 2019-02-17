#include "ModelObject.h"



ModelObject::ModelObject(MyScene *scene, string filePath) : WorldObject(scene, 0, "test", 0),
	scene(scene), _flagAutospin(false),
	_flagReset(false), _iKey(false), _jKey(false), _kKey(false),
	_lKey(false), _oKey(false), _uKey(false), _plusKey(false), _minusKey(false),
	_upKey(false), _downKey(false), _leftKey(false), _rightKey(false)
{
	_path = filePath;


	objectFileReader	= new ObjectFileReader(_path);
	objectFileReader->Load();

	vertices			= objectFileReader->vertices;
	normals				= objectFileReader->normals;
	textureCoordinates	= objectFileReader->textureCoordinates;
	faces				= objectFileReader->faces;
	faceMaterials		= objectFileReader->faceMaterials;
}


ModelObject::~ModelObject()
{
}

void ModelObject::Display() {
	glPushMatrix();
	glDisable(GL_LIGHTING);
	
	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0] * 1, scale[1] * 1, scale[2] * 1);

	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f); // angle ry about (0,1,0)
	glRotatef(rotation[2], 0.0f, 0.0f, 1.0f); // angle rz about (0,0,1)
	glRotatef(rotation[0], 1.0f, 0.0f, 0.0f); // angle rx about (1,0,0)

	Render();

	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void ModelObject::Render() {
	//glEnable(GL_TEXTURE_2D);
	//glEnable(GL_COLOR_MATERIAL);

	//glBindTexture(GL_TEXTURE_2D, textureId);
	glColor4f(1.f, 1.f, 1.f, 1.f);

	glBegin(GL_TRIANGLES);

	//bool alreadyRendered = false;
	for (size_t faceId = 0; faceId < faces.size(); faceId++) {
		RenderFace(faces[faceId]);
	}

	glEnd();
	
}

void ModelObject::RenderFace(int ** face) {
	float r, g, b, x, y ,z;
	float min = -10.0;
	float max = 10.0;

	for (auto vertexId = 0; vertexId < 3; vertexId++) {
		auto vertex = face[vertexId];
		auto vertexCoordinates = vertices[vertex[0]];
		x = vertexCoordinates->x;
		y = vertexCoordinates->y;
		z = vertexCoordinates->z;

		r = FloatNormalise(x, min, max);
		g = FloatNormalise(y, min, max);
		b = FloatNormalise(z, min, max);
		glColor3f(r, g, b);
		glVertex3f(x, y, z);
	}
}

void ModelObject::Update(const double& deltaTime) {
	float velocity = 100.0f*static_cast<float>(deltaTime);
	float shrinkRate = -50.0f*static_cast<float>(deltaTime);

	if (abs(scene->rx) > 10) rotation[1] += scene->rx / 16.f;
	if (abs(scene->ry) > 10) rotation[0] -= scene->ry / 16.f;

	if (abs(scene->lx) > 10) pos[0] += scene->lx / 128.0f;
	if (abs(scene->ly) > 10) pos[2] += scene->ly / 128.0f;

	if (abs(scene->lt) > 10) {
		scale[0] += shrinkRate;
		scale[1] += shrinkRate;
		scale[2] += shrinkRate;
	}

	if (abs(scene->rt) > 10) {
		scale[0] -= shrinkRate;
		scale[1] -= shrinkRate;
		scale[2] -= shrinkRate;
	}
	
	// Spacebar will reset transformation values
	if (_flagReset)
	{
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


void ModelObject::HandleKey(unsigned char key, int state, int x, int y)
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

void ModelObject::HandleSpecialKey(int key, int state, int x, int y)
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