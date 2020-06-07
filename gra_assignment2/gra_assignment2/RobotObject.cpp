#include "RobotObject.h"


RobotObject::RobotObject(MyScene* scene, int id, std::string objectName, ColorRGB* color) :
	WorldObject(scene, id, objectName, color),
	_flagReset(false), _iKey(false), _jKey(false), _kKey(false),
	_lKey(false), _oKey(false), _uKey(false), _plusKey(false), _minusKey(false),
	_upKey(false), _downKey(false), _leftKey(false), _rightKey(false)
{
	size(_INIT_SIZE);
	newObjects = new std::vector<WorldObject*>;

	pos[1] = 100.0f;
}


RobotObject::~RobotObject()
{
}

void RobotObject::Display() {
	glPushMatrix();
	glDisable(GL_LIGHTING);

	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);
	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f); // angle ry about (0,1,0)
	glRotatef(rotation[2], 0.0f, 0.0f, 1.0f); // angle rz about (0,0,1)
	glRotatef(rotation[0], 1.0f, 0.0f, 0.0f); // angle rx about (1,0,0)

	DrawRobot();

	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void RobotObject::DrawRobot()
{

	glClearColor(0, 0, 0, 0);
	glTranslatef(0.f, 2.f, 0.f);
	DrawHead(R);
	//DrawSphere(R,5);
	glTranslatef(0.f, -R, 0.f);

	glPushMatrix();
	DrawArm(arm_length, arm_r, 0);
	glPopMatrix();

	glPushMatrix();
	DrawArm(arm_length, arm_r, 1);
	glPopMatrix();

	glPushMatrix();
	DrawBody(body_width, body_length, body_height);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-body_width / 2, -body_height / 7, 0);
	glColor3f(0.5f, 0.5f, 0.5f);
	DrawSphere(joint_r, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(body_width / 2, -body_height / 7, 0);
	glColor3f(0.5f, 0.5f, 0.5f);
	DrawSphere(joint_r, 5);
	glPopMatrix();

	glTranslatef(0.f, -body_height, 0.f);

	glPushMatrix();
	DrawLeg(leg_length, leg_r, 0);
	glPopMatrix();

	glPushMatrix();
	DrawLeg(leg_length, leg_r, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(body_width / 2, 0, 0);
	glColor3f(0.5f, 0.5f, 0.5f);
	DrawSphere(1.1*leg_r / sqrt(2), 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-body_width / 2, 0, 0);
	glColor3f(0.5f, 0.5f, 0.5f);
	DrawSphere(1.1*leg_r / sqrt(2), 5);
	glPopMatrix();

}

void RobotObject::DrawHead(float R)
{
	glPushMatrix();
	glColor3f(0.7, 0.3, 0.1);
	DrawSphere(R, 5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.4, 0.7);
	glTranslatef(-R / 2, 0.f, R);
	glutSolidCube(R / 4);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.4, 0.7);
	glTranslatef(R / 2, 0.f, R);
	glutSolidCube(R / 4);
	glPopMatrix();
}


void RobotObject::Update(const double& deltaTime)
{
	/*
	The update function gives a smooth motion between frames.
	Update is called before drawing every frame so we can use it to
	update the cubes position and rotation each frame.
	The input argument (deltaTime) gives you how many seconds
	have passed between calling the Update function, so we can
	use it define the speed of an object. If we want a object to
	transform by 100 units each second and deltaTime represents
	how many seconds have passed betweeen rendering the last frame
	and the this then we can multiply 100*deltaTime to calculate
	the tranform for this frame at a rate of 100 units per second.
	*/
	float velocity = 100.0f*static_cast<float>(deltaTime);
	float shrinkRate = -50.0f*static_cast<float>(deltaTime);

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

void RobotObject::HandleKey(unsigned char key, int state, int x, int y)
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
	}
}

void RobotObject::HandleSpecialKey(int key, int state, int x, int y)
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


void RobotObject::DrawArm(float length, float r, int dir)
{
	glColor3f(0.7f, 0.7f, 0.f);
	if (dir == 0) // left arm
	{

	}
	else  // right arm
	{
		glRotatef(180.f, 0.f, 1.f, 0.f);
	}
	glTranslatef(-body_width / 2 - sqrt(3)*arm_length / 8, -arm_length / 4, 0.f);
	glRotatef(-60.f, 0.f, 0.f, 1.f);
	glScalef(r, length / 2, r);

	glutSolidCube(1.f);

	glScalef(1 / r, 2 / length, 1 / r); // reverse

	glTranslatef(0.f, -length / 4, 0.f);
	glColor3f(0.2f, 0.1f, 0.1f);
	DrawSphere(joint_r, 3);

	glTranslatef(length / 4 + 0.1f, -length / 4 + 0.1f, 0.f);
	glRotatef(60.f, 0.f, 0.f, 1.f);

	glColor3f(0.7f, 0.7f, 0.f);
	glScalef(r, length / 2, r);
	glutSolidCube(1.f);

	glScalef(1 / r, 2 / length, 1 / r); // reverse
}

void RobotObject::DrawLeg(float length, float r, int dir)
{
	glColor3f(0.7f, 0.2f, 0.f);
	if (dir == 0) // left aleg
	{

	}
	else  // right leg
	{
		glRotatef(180.f, 0.f, 1.f, 0.f);
	}
	//glTranslatef(-body_width / 2 + leg_r / 4, -length / 4 - leg_r / 2, 0.f);

	glTranslatef(-body_width / 2 - length / 8, -length * sqrt(3) / 8, 0.f);
	glRotatef(-30.f, 0.f, 0.f, 1.f);

	glScalef(r, length / 2, r);
	glutSolidCube(1.f);
	glScalef(1 / r, 2 / length, 1 / r); // re-scale

	glTranslatef(0.f, -length / 4, 0.f);
	glColor3f(0.5f, 0.5f, 0.5f);
	DrawSphere(1.1*r / sqrt(2), 5);

	glRotatef(30.f, 0.f, 0.f, 1.f);
	glTranslatef(0.f, -length / 4, 0.f);

	glScalef(r, length / 2, r);
	glColor3f(0.7f, 0.2f, 0.f);
	glutSolidCube(1.f);

	glScalef(1 / r, 2 / length, 1 / r); // re-scale
}

void RobotObject::DrawBody(float width, float length, float height)
{
	glColor3f(0.1f, 0.2f, 0.1f);

	glTranslatef(0.f, -height / 2, 0.f);
	glScalef(width, height, length);
	glutSolidCube(1.f);


}

void RobotObject::DrawSphere(float R, int depth)
{
	GLfloat A[3] = { 0,R,0 };
	GLfloat B[3] = { -R,0,0 };
	GLfloat C[3] = { 0,0,-R };
	GLfloat D[3] = { R,0,0 };
	GLfloat E[3] = { 0,0,R };
	GLfloat F[3] = { 0,-R,0 };

	Subdivide(A, E, D, depth, R);
	Subdivide(A, B, E, depth, R);
	Subdivide(A, C, B, depth, R);
	Subdivide(A, D, C, depth, R);
	Subdivide(F, D, E, depth, R);
	Subdivide(F, E, B, depth, R);
	Subdivide(F, B, C, depth, R);
	Subdivide(F, C, D, depth, R);
}

void RobotObject::Subdivide(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], int depth, float r)
{
	GLfloat v12[3], v23[3], v13[3] = { 0,0,0 };

	int i;

	if (depth == 0) {
		glBegin(GL_TRIANGLES);
		glVertex3f(v1[0], v1[1], v1[2]); //b
		glVertex3f(v2[0], v2[1], v2[2]);  //d
		glVertex3f(v3[0], v3[1], v3[2]); //c
		glEnd();
		return;
	}
	else
	{
		/* calculate midpoints of each side */
		for (i = 0; i < 3; i++) {
			v12[i] = (v1[i] + v2[i]) / 2.0f;
			v23[i] = (v2[i] + v3[i]) / 2.0f;
			v13[i] = (v3[i] + v1[i]) / 2.0f;
		}

		normalize(v12, r);
		normalize(v23, r);
		normalize(v13, r);

		Subdivide(v1, v12, v13, depth - 1, r);
		Subdivide(v2, v23, v12, depth - 1, r);
		Subdivide(v3, v13, v23, depth - 1, r);
		Subdivide(v12, v23, v13, depth - 1, r);
	}
}

void RobotObject::normalize(GLfloat v[3], float R)
{
	GLfloat d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] = v[0] / d * R; v[1] = v[1] / d * R; v[2] = v[2] / d * R;
}

void RobotObject::DrawJoint(float h, float r)
{
	float res = 0.1f * M_PI;           // resolution (in radians: equivalent to 18 degrees)
	float x = r, z = 0.f;           // initialise x and z on right of cylinder centre
	float t = 2.f * M_PI;                  // initialise angle as 0
	
	do
	{
		glColor3f(0.6f, 0.2f, 0.2f);
		glBegin(GL_QUADS);          // new QUAD
									// Create first points
		glVertex3f(x, h, z);    // top
		glVertex3f(x, 0.f, z);  // bottom
								// Iterate around circle
		t -= res;               // add increment to angle
		x = r * cos(t);           // move x and z around circle
		z = r * sin(t);
		// Close quad
		glVertex3f(x, 0.f, z);  // bottom
		glVertex3f(x, h, z);    // top
		glEnd();                    // end shape
	} while (t >= 0);        // for a full circle (360 degrees)
	glBegin(GL_POLYGON);
	glColor3f(0.2f, 0.1f, 0.1f);
	for (int i = 0; i < 3600; i++)
	{
		glVertex3f(r*cos(2 * M_PI*i / 3600), 0.f, r*sin(2 * M_PI*i / 3600));
		//glVertex3f(r*cos(2 * M_PI*i / 3600), h, r*sin(2 * M_PI*i / 3600));
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 3600; i >0; i--)
	{
		//glVertex3f(r*cos(2 * M_PI*i / 3600), 0.f, r*sin(2 * M_PI*i / 3600));
		glVertex3f(r*cos(2 * M_PI*i / 3600), h, r*sin(2 * M_PI*i / 3600));
	}
	glEnd();
}