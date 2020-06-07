#include "PlayerObject.h"

PlayerObject::PlayerObject(MyScene* scene, int id, std::string objectName, ColorRGB* color) :
	WorldObject(scene, id, objectName, color),
	_flagReset(false), _iKey(false), _jKey(false), _kKey(false),
	_lKey(false), _oKey(false), _uKey(false), _plusKey(false), _minusKey(false),
	_upKey(false), _downKey(false), _leftKey(false), _rightKey(false),
	_wKey(false), _sKey(false), _aKey(false), _dKey(false), _shiftKey(false), _fKey(false)
{
	size(_INIT_SIZE);
}


PlayerObject::~PlayerObject()
{
}

void PlayerObject::Display() {
	/* This function is used to initialise rendering to the screen
	** I call several functions from it to render different parts of the model
	*/

	/* Get the texture */
	texId = scene->GetTexture(_tex_path);

	glPushMatrix();
	glEnable(GL_LIGHTING);

	/* Enable all the lights that are currently registered in MyScene */
	for (size_t i = 0; i < scene->lights->size(); ++i) {
		glEnable(GL_LIGHT0 + (int)i);
	}

	/* Translate origin of the model, scale and rotate from given values */
	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);
	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f); // angle ry about (0,1,0)
	glRotatef(rotation[2], 0.0f, 0.0f, 1.0f); // angle rz about (0,0,1)
	glRotatef(rotation[0], 1.0f, 0.0f, 0.0f); // angle rx about (1,0,0)

	/* Update ambient and diffuse light attributes from given value */
	mat_ambient[0] = light_color->x;
	mat_ambient[1] = light_color->y;
	mat_ambient[2] = light_color->z;
	mat_diffuse[0] = light_color->x;
	mat_diffuse[1] = light_color->y;
	mat_diffuse[2] = light_color->z;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	
	/* Begin rendering the model */
	DrawPlayer();
	
	glDisable(GL_LIGHTING);
	glPopMatrix();
}

void PlayerObject::DrawPlayer() {
	/* In this function, I call several other functions to render
	** different parts of the model
	** The translations, and rotations of these parts is arbitrary
	** to this specific model
	** Colours are averaged from the given ColorRGB *color and arbitrary values
	** (mostly white) to give a better fit in the scene.
	*/

	// Head
	glClearColor(0, 0, 0, 0);
	glTranslatef(0.f, 2.f, 0.f);
	DrawHead(R);
	glTranslatef(0.f, -R, 0.f);

	// Arms
	glPushMatrix();
	DrawArm(arm_length, arm_r, 0);
	glPopMatrix();

	glPushMatrix();
	DrawArm(arm_length, arm_r, 1);
	glPopMatrix();

	// Torso
	glPushMatrix();
	DrawBody(body_width, body_length, body_height);
	glPopMatrix();

	float red, gre, blu;

	red = (color->x + 0.7f) / 2.f;
	gre = (color->y + 0.1f) / 2.f;
	blu = (color->z + 0.1f) / 2.f;

	/* Shoulder Joints */
	glPushMatrix();
	glTranslatef(-body_width / 2.f, -body_height / 7.f, 0.f);
	glColor3f(red, gre, blu);
	DrawSphere(joint_r, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(body_width / 2.f, -body_height / 7.f, 0.f);
	glColor3f(red, gre, blu);
	DrawSphere(joint_r, 5);
	glPopMatrix();

	/* Translate to the bottom of the model to render the legs */
	glTranslatef(0.f, -body_height, 0.f);

	// Legs
	glPushMatrix();
	DrawLeg(leg_length, leg_r, 0);
	glPopMatrix();

	glPushMatrix();
	DrawLeg(leg_length, leg_r, 1);
	glPopMatrix();

	red = (color->x + 0.12f) / 2.f;
	gre= (color->y + 0.56f) / 2.f;
	blu = (color->z + 1.0f) / 2.f;

	/* Hip Joints */
	// Right
	glPushMatrix();
	glTranslatef(body_width / 2.f - leg_r / 2.f, 0, 0);
	glColor3f(red, gre, blu);
	DrawSphere(leg_r / 1.5f, 5);
	glPopMatrix();

	// Left
	glPushMatrix();
	glTranslatef(-body_width / 2.f + leg_r / 2.f, 0.f, 0.f);
	glColor3f(red, gre, blu);
	DrawSphere(leg_r / 1.5f, 5);
	glPopMatrix();

}

void PlayerObject::DrawHead(float R) {
	/* This function draws the head of the model
	** A texture is applied to the head
	*/

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texId);

	glColor3f((color->x + 1) / 2.f, (color->y + 1) / 2.f, (color->z + 1) / 2.f);
	glRotatef(-90.0, 1, 0, 0);
	DrawSphere(R, 5);
	glRotatef(90.0, 1, 0, 0);

	
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void PlayerObject::DrawArm(float length, float r, int dir) {
	/* This function draws an arm of the model */
	float red, gre, blu;

	red = (color->x + 0.7f) / 2;
	gre = (color->y + 0.1f) / 2;
	blu = (color->z + 0.1f) / 2;

	glColor3f(red, gre, blu);

	/* These variables used for animation */
	float mult;
	float lower_angle = lower_arm_angle;
	float upper_angle = upper_arm_angle;

	/* dir determines whether the arm is rendered on the left or right
	** side of the body, and also determines the angle by which the arm
	** rotates
	*/
	if (dir == 0) {
		// left arm
		mult = -1;
		lower_angle = (low_angle_max - lower_angle) * walking;
		if (interacting) upper_angle = 0.f;
	}
	else  {
		// right arm
		// rotate 180 degrees around to flip the arm
		glRotatef(180.f, 0.f, 1.f, 0.f);
		mult = 1;
	}

	if (interacting) {
		lower_angle = 0.f;
	}

	/* Drawing the upper arm */
	glTranslatef(0.f, -0.25f, 0.0f); //
	glRotatef(upper_angle, 1.0f, 0.f, 0.f);
	glTranslatef(-body_width / 2.f - arm_length / 8.f + arm_r / 2.f, -arm_length / 4.f, 0.f);
	glRotatef(-arm_angle, 0.f, 0.f, 1.f);

	glScalef(r, length / 2, r); // set scale of this part of the arm
	glutSolidCube(1.f);
	glScalef(1 / r, 2 / length, 1 / r); // reverse scaling

	glTranslatef(0.f, (-length / 4), 0.0f);
	DrawSphere(joint_r*1.2f, 3);  // draw the arm joint

	/* Drawing the lower arm */
	glRotatef(mult * lower_angle, 1.0f, 0.f, 0.f);
	glTranslatef(0, (-length / 4.0f) + (joint_r / 2.0f), 0.0f);

	red = (color->x + 1.0f) / 2;
	gre = (color->y + 0.95f) / 2;
	blu = (color->z + 0.7f) / 2;

	glColor3f(red, gre, blu);
	glScalef(r, length / 2, r); // set scale of this part of the arm
	glutSolidCube(1.f); // draw the lower part of the arm

	glTranslatef(0.0f, 0.0f, 0.0f);

	glScalef(1 / r, 2 / length, 1 / r); // reverse scaling
}

void PlayerObject::DrawLeg(float length, float r, int dir) {
	/* This function draws a leg of the model */
	float red, gre, blu;

	red = (color->x + 0.12f) / 2;
	gre = (color->y + 0.56f) / 2;
	blu = (color->z + 1.0f) / 2;

	glColor3f(red, gre, blu);
	
	/* These variables used for animation */
	float mult;
	float lower_angle = lower_arm_angle;
	float upper_angle = upper_arm_angle;

	/* dir determines whether the leg is rendered on the left or right
	** side of the body, and also determines the angle by which the leg
	** rotates
	*/
	if (dir == 0) {
		// left leg 
		mult = -1;
		lower_angle = (low_angle_max - lower_angle) * walking;
	}
	else {
		// right leg
		// rotate 180 degrees around to flip the leg
		glRotatef(180.f, 0.f, 1.f, 0.f);
		mult = 1;
	}

	if (interacting) {
		upper_angle = 0;
		lower_angle = 0;
	}
	
	/* Drawing the upper leg */
	glRotatef(-upper_angle, 1.0f, 0.f, 0.f);
	glTranslatef(-body_width / 4.0f - leg_r / 4.0f, -length / 4.0f - leg_r / 4.0f, 0.f);
	glRotatef(-leg_angle, 0.f, 0.f, 1.f);
	glScalef(r, length / 2, r);
	glutSolidCube(1.f);
	glScalef(1 / r, 2 / length, 1 / r); // re-scale

	glTranslatef(0.f, -length / 4, 0.f);
	DrawSphere((float) r / sqrt(2.0f), 5); // draw the leg joint

	/* Drawing the lower leg */
	glRotatef(-mult * lower_angle, 1.0f, 0.f, 0.f);
	glRotatef(leg_angle, 0.f, 0.f, 1.f);
	glTranslatef(0.f, -length / 4, 0.f);
	glScalef(r, length / 2.f, r); // set scale of this part of the leg

	red = (color->x + 1.0f) / 2;
	gre = (color->y + 0.95f) / 2;
	blu = (color->z + 0.7f) / 2;

	glColor3f(red, gre, blu);
	// draw the lower part of the leg
	glutSolidCube(1.f);

	glRotatef(-leg_angle, 0.f, 0.f, 1.f);

	glScalef(1.f / r, 2.f / length, 1.f / r); // reverse scaling

	/* Drawing the foot */
	glTranslatef(0.f, -(length / 4.f) , -mult * (-0.1f + r * 0.5f));
	glScalef(r + 0.1f, r / 1.5f, r * 2.f); // set scale of the foot

	red = 0.3f * (color->x + 0.38f) / 2.f;
	gre = 0.3f * (color->y + 0.15f) / 2.f;
	blu = 0.3f * (color->z + 0.05f) / 2.f;
	glColor3f(red, gre, blu);
	
	glutSolidCube(1.f);
	glScalef(1.f / (r + 0.1f), r * 1.5f, r / 2.f); // reverse scaling	
}

void PlayerObject::DrawBody(float width, float length, float height) {
	/* This function draws the body of the model */
	float red, gre, blu;

	red = (color->x + 0.76f) / 2;
	gre = (color->y + 0.16f) / 2;
	blu = (color->z + 0.16f) / 2;

	glColor3f(red, gre, blu);
	glTranslatef(0.f, -height / 2, 0.f);
	glScalef(width, height, length);
	glutSolidCube(1.f);
}

void PlayerObject::DrawSphere(float R, int depth) {
	/* This function creates and draws a textured sphere
	** that is used as the head of the model
	*/
	GLUquadricObj *sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);

	gluSphere(sphere, R, 10, 10);
}

void PlayerObject::Update(const double& deltaTime) {
	/* This function is called whenever the scene is updated
	** deltaTime refers to the change in time since the previous update
	** In this function, I set the angles and position of the model to
	** animate it
	*/

	float velocity = speed / 2.f;
	float shrinkRate = -50.0f*static_cast<float>(deltaTime);

	/* Idling animation, move arms slightly inwards and outwards */
	arm_angle = 10.f + sin(glutGet(GLUT_ELAPSED_TIME) / 500.f) * 5.f;

	/*
	** If keys pressed down: 
	**      [/\ ]
	** [<- ][\/ ][ ->]
	** or
	**      [ w ]
	** [ a ][ s ][ d ]
	** 
	** Translate along x and z axes, for (left, right) and (forward, back) respectively
	*/

	/* If there is an XINPUT controller connected, use that */
	XInputController *controller = scene->GetController(); // Get the current controller
	bool connected = controller->IsConnected(); // Check if a controller is connected
	bool _upStick = false, _downStick = false, _leftStick = false, _rightStick = false, _bButton = false; // Flags for different inputs
	if (connected) {
		SHORT left[2] = { 0, 0 };	// x,y values for the left thumbstick
		SHORT right[2] = { 0, 0 };	// x,y values for the right thumbstick

		/* Button enabling */
		if (controller->GetGamepadState().wButtons & XINPUT_GAMEPAD_A) {
			interacting = true;
		}
		if (controller->GetGamepadState().wButtons & XINPUT_GAMEPAD_B) {
			_bButton = true;
		}

		/* Set x,y values for left and right thumbsticks from gamepad state */
		left[0] = (SHORT)(controller->GetGamepadState().sThumbLX);
		left[1] = (SHORT)(controller->GetGamepadState().sThumbLY);
		right[0] = (SHORT)(controller->GetGamepadState().sThumbRX);
		right[1] = (SHORT)(controller->GetGamepadState().sThumbRY);

		SHORT threshold = 2048; // threshold for dead zone
		if (abs(left[0]) < threshold) left[0] = 0;
		if (abs(left[1]) < threshold) left[1] = 0;
		if (abs(right[0]) < threshold) right[0] = 0;
		if (abs(right[1]) < threshold) right[1] = 0;

		/* Use the right stick to rotate the player character around */
		float rightAngle = (float)(atan2(right[1], right[0]) * 180.f / PI);

		/* Set the angle to be the last updated angle when the stick returns to the neutral position
		** Otherwise add 90 degrees to the rotation
		*/
		if (right[0] == 0 && right[1] == 0) {
			rotation[1] = prevRot;
		}
		else {
			rotation[1] = rightAngle + 90;
			prevRot = rightAngle + 90;
		}

		/* Set boolean values for walking around */
		_downStick = left[1] < -threshold;
		_upStick = left[1] > threshold;
		_rightStick = left[0] > threshold;
		_leftStick = left[0] < -threshold;
	}

	/* Set boolean values based on current keys pressed */
	up = (_upKey || _wKey || _upStick);
	dn = (_downKey || _sKey || _downStick);
	lf = (_leftKey || _aKey || _leftStick);
	rt = (_rightKey || _dKey || _rightStick);



	/* If the user is pressing shift, then double the speed which they move */
	if (_shiftKey || _bButton) velocity *= 2;

	/* Interaction prevents the player from moving 
	** If they are not interacting, then move the player and rotate the model
	** to face the direction they are moving in
	** This also checks that the player is within the bounds of the scene
	*/
	if (!interacting) {
		if (up && !dn) {
			if (pos[2] - velocity > _ZBOUND_MIN) pos[2] -= velocity;
			rotation[1] = 180.f;
		}
		if (dn && !up) {
			if (pos[2] + velocity < (_ZBOUND_MAX * 2) - 50) pos[2] += velocity;
			rotation[1] = 0.f;
		}
		if (lf && !rt) {
			if (pos[0] - velocity > _XBOUND_MIN) pos[0] -= velocity;
			rotation[1] = 290.f;
		}
		if (rt && !lf) {
			if (pos[0] + velocity < _XBOUND_MAX) pos[0] += velocity;
			rotation[1] = 70.f;
		}

		/* Diagonal angles */
		if (up && rt && !(dn || lf)) {
			rotation[1] = 135.f;
		}
		if (up && lf && !(dn || rt)) {
			rotation[1] = 215.f;
		}
		if (dn && rt && !(up || lf)) {
			rotation[1] = 45.f;
		}
		if (dn && lf && !(up || rt)) {
			rotation[1] = 315.f;
		}
	}

	prevRot = rotation[1];

	/* Reset the walking state */
	walking = false;

	/* If the player has moved, and values do not conflict
	** e.g. walking both left and right at the same time
	** Then set the walking state to true
	*/
	if (lf || rt) {
		if (lf != rt) {
			walking = true;
		}
	}
	if (up || dn) {
		if (up != dn) {
			walking = true;
		}
	}

	float animation_speed = speed;

	low_angle_min = lower_limb_min_angle;
	low_angle_max = lower_limb_max_angle;
	upper_angle_min = upper_limb_min_angle;
	upper_angle_max = upper_limb_max_angle;

	/* If the player is not sprinting, then half their animation speed */
	if (!(_shiftKey || _bButton)) {
		animation_speed /= 2.f;
		low_angle_min /= 2.f;
		low_angle_max /= 2.f;
		upper_angle_min /= 2.f;
		upper_angle_max /= 2.f;
	}


	/* If the arm angle has reached its upper or lower limit, change the direction */
	if (upper_arm_angle <= upper_angle_min) {
		animation_dir *= -1.f;
		upper_arm_angle = upper_angle_min;
	}
	if (upper_arm_angle >= upper_angle_max) {
		animation_dir *= -1.f;
		upper_arm_angle = upper_angle_max;
	}

	/* Increment the angles based on the predefined speed, and calculated direction */
	upper_arm_angle += animation_dir * animation_speed;
	lower_arm_angle += animation_dir * animation_speed;

	/* Here I check the bounds of the lower angle, this is used to give the
	** walking animation a more realistic appearance
	*/
	if (lower_arm_angle <= low_angle_min) {
		lower_arm_angle = low_angle_min;
	}
	if (lower_arm_angle >= low_angle_max) {
		lower_arm_angle = low_angle_max;
	}

	/* If the use has pressed the [f] key, then set the interacting state to true */
	if (_fKey) interacting = true;

	/* If the player is interacting, then increment a timer that lasts for a set
	** amount of time, once that time has passed, set the interacting state to false
	** and reset the angles of the player
	*/
	if (interacting) {
		timeCount += (float)deltaTime;

		if (timeCount < timeDelay) {
			// Set angles for interacting animation
			upper_arm_angle = 45.f;
			lower_arm_angle = 0.f;
			interacting = true;
		}
		else {
			// reset
			interacting = false;
			upper_arm_angle = 0.f;
			lower_arm_angle = 0.f;
			timeCount = 0.f;
		}
	}

	/* If the player is neither walking nor interacting with anything,
	** then set the player into a neutral state
	*/
	if (!(walking || interacting)) {
		upper_arm_angle = 0.f;
		lower_arm_angle = 0.f;
	}

}

void PlayerObject::HandleKey(unsigned char key, int state, int x, int y) {
	/* This function is used to handle key input and set boolean flags
	** based on which keys have been pressed
	** It can also determine if the shift key has been pressed for certain keys
	*/

	if (_shiftKey && !static_cast<GLboolean>(state))
		_shiftKey = false; // set the shift state to false

	/* Check if the character pressed is in uppercase, if so, set the shift key
	** state to true
	*/
	if (isupper(key)) {
		_shiftKey = static_cast<GLboolean>(state);
		key = tolower(key);
	}

	/* Set flags based on the keys being pressed */
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
	case 'w':
		_wKey = static_cast<GLboolean>(state);
		break;
	case 's':
		_sKey = static_cast<GLboolean>(state);
		break;
	case 'a':
		_aKey = static_cast<GLboolean>(state);
		break;
	case 'd':
		_dKey = static_cast<GLboolean>(state);
		break;
	case 'f':
		_fKey = static_cast<GLboolean>(state);
		break;
	case ' ':
		_flagReset = true;
		break;
	}
}

void PlayerObject::HandleSpecialKey(int key, int state, int x, int y) {
	/* This function is used to determine whether special keys are being pressed
	** e.g. the cursor keys, and set flags accordingly
	*/
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

