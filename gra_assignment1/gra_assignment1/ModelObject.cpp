#include "ModelObject.h"

ModelObject::ModelObject(MyScene *scene, string fileName, Vertex * color, int winding) : WorldObject(scene, 0, "test", 0),
	scene(scene), _flagAutospin(false),
	_flagReset(false), _iKey(false), _jKey(false), _kKey(false),
	_lKey(false), _oKey(false), _uKey(false), _plusKey(false), _minusKey(false),
	_upKey(false), _downKey(false), _leftKey(false), _rightKey(false)
{
	_obj_path = "Obj/" + fileName + ".obj";
	_tex_path = "Texture/" + fileName + ".bmp";
	_tex_path2 = "Texture/" + fileName + "2.bmp";
	defaultColor = color;

	objectFileReader = new ObjectFileReader(_obj_path);
	objectFileReader->Load();

	vertices = objectFileReader->vertices;
	normals = objectFileReader->normals;
	textureCoordinates = objectFileReader->textureCoordinates;
	faces = objectFileReader->faces;
	faceMaterials = objectFileReader->faceMaterials;

	//glFrontFace(winding);

	static GLfloat mat_ambient[] = { 0.f, 0.f, 0.9f, 1.f };
	// Define the diffuse material colour property K_d
	static GLfloat mat_diffuse[] = { 0.9f, 0.0f, 0.0f, 1.f };
	// Define the specular material colour property K_s
	static GLfloat mat_specular[] = { 1.f, 1.f, 1.f, 1.f };
	// Define the shininess/specular exponent factor n ( capped between 0.0 and 128.0 )
	static GLfloat mat_shininess[] = { 30.0f };

	_mat_ambient = mat_ambient;
	_mat_diffuse = mat_diffuse;
	_mat_specular = mat_specular;
	_mat_shininess = mat_shininess;

	size(_INIT_SIZE);
	pos[2] = _DEF_Z * 2;

	_texID = scene->GetTexture(_tex_path);
	_texID2 = scene->GetTexture(_tex_path2);
}


ModelObject::~ModelObject()
{
}

void ModelObject::Display() {
	glPushMatrix();	
	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);

	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f); // angle ry about (0,1,0)
	glRotatef(rotation[2], 0.0f, 0.0f, 1.0f); // angle rz about (0,0,1)
	glRotatef(rotation[0], 1.0f, 0.0f, 0.0f); // angle rx about (1,0,0)

	glMaterialfv(GL_FRONT, GL_AMBIENT, _mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _mat_diffuse);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _texID);
	glColor3f(1, 1, 1);
	glutSolidSphere(1, 1, 1);
	Render();

	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void ModelObject::Render() {
	//glEnable(GL_TEXTURE_2D);
	//glEnable(GL_COLOR_MATERIAL);

	//glBindTexture(GL_TEXTURE_2D, textureId);
	//float light_position[] = { 0.0f, 1.0f, 0.0f, 0.0f };
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//glColor3f(defaultColor->x, defaultColor->y, defaultColor->z);

	//auto alreadyRenderedFaces = false;
	//auto currentTextureId = Materials::NONE;


	for (size_t faceId = 0; faceId < faces.size(); faceId++) {
		//auto faceMaterial = faceMaterials[faceId];
		//auto textureChanged = faceMaterial != currentTexture;

		Face * face = faces[faceId];
		glColor3f(.5f, .5f, .5f);
		if (face->faceData->size() == 3) {
			glBegin(GL_TRIANGLES);
		}
		else {
			glBegin(GL_QUADS);
		}
		RenderFace(face);
		glEnd();
	}
	
}

void ModelObject::RenderFace(Face * face) {

	vector<Vertex*> *faceData = face->faceData;

	for (size_t vertexId = 0; vertexId < faceData->size(); ++vertexId) {
		Vertex * data = faceData->at(vertexId);

		int normalIndex = (int)data->z; // Index position of the normal within the normals list
		if (normalIndex > -1 && normalIndex < (int) normals.size())
			RenderNormal(normalIndex);
		
		int materialIndex = (int)data->y; // Index position of the material within the materials list
		if (materialIndex > -1 && materialIndex < (int) textureCoordinates.size())
			RenderMaterial(materialIndex);

		int vertexIndex = (int)data->x; // Index position of the vertex within the vertices list
		if (vertexIndex > -1 && vertexIndex < (int)vertices.size())
			RenderVertex(vertexIndex);
		
	}
}

void ModelObject::RenderVertex(int vertexIndex) {
	Vertex * vertexCoordinates = vertices[vertexIndex];
	glVertex3f(vertexCoordinates->x, vertexCoordinates->y, vertexCoordinates->z);
}

void ModelObject::RenderNormal(int normalIndex) {
	auto normal = normals[normalIndex];
	glNormal3f(normal->x, normal->y, normal->z);
	//glColor3f(normal->x, normal->y, normal->z);
}

void ModelObject::RenderMaterial(int materialIndex) {
	float * materialCoordinate = textureCoordinates[materialIndex];
	float one = materialCoordinate[0];
	float two = materialCoordinate[1];
	glTexCoord2f(materialCoordinate[0], materialCoordinate[1]);
}

void ModelObject::setScale(Vertex * size) {
	this->vSize = size;
	scale[0] = vSize->x;
	scale[1] = vSize->y;
	scale[2] = vSize->z;
}

void ModelObject::setPosition(Vertex * position) {
	this->vPosition = position;
	//position(vPosition->x, vPosition->y, vPosition->z);
	pos[0] = vPosition->x;
	pos[1] = vPosition->y;
	pos[2] = vPosition->z;

}

void ModelObject::setOrientation(Vertex * orientation) {
	this->vOrientation = orientation;
	rotation[0] = vOrientation->x;
	rotation[1] = vOrientation->y;
	rotation[2] = vOrientation->z;
}

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
void ModelObject::Update(const double& deltaTime) {
	float velocity = 100.0f*static_cast<float>(deltaTime);
	float shrinkRate = -5.0f*static_cast<float>(deltaTime);

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
		PlaySound(TEXT("naruto.wav"), NULL, SND_FILENAME | SND_ASYNC);
		size(vSize->x, vSize->y, vSize->z);
		position(vPosition->x, vPosition->y, vPosition->z);
		orientation(vOrientation->x, vOrientation->y, vOrientation->z);
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

	/*
	faceY
		up = 0;
		down = 1;
	faceX
		left = 0;
		right = 1;
	*/
	float current = rotation[1];
	
	if (_upKey) {
		pos[2] -= velocity;

		if (rotation[1] > -180.0) rotation[1] -= 30;
		if (rotation[1] < -180.0) rotation[1] += 30;
	}
	if (_downKey) {
		pos[2] += velocity;
		if (rotation[1] > 0) rotation[1] -= 30;
		if (rotation[1] < 0) rotation[1] += 30;
	}

	if (_leftKey) {
		pos[0] -= velocity;
		if (rotation[1] > -90) rotation[1] -= 30;
		if (rotation[1] < -90) rotation[1] += 30;
	}
	if (_rightKey) {
		pos[0] += velocity;
		if (rotation[1] > 90) rotation[1] -= 30;
		if (rotation[1] < 90) rotation[1] += 30;
	}

	if (_pageDn) {
		pos[1] -= velocity;
	}
	if (_pageUp) {
		pos[1] += velocity;
	}
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
		break;
		//if (state == 0) {
			//_flagAutospin = !_flagAutospin;
			//break;
		//}
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
	case GLUT_KEY_PAGE_UP:
		_pageUp = static_cast<GLboolean>(state);
		break;
	case GLUT_KEY_PAGE_DOWN:
		_pageDn = static_cast<GLboolean>(state);
		break;
	}
}