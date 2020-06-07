#include "CatObject.h"

CatObject::CatObject(MyScene* scene, int id, std::string objectName, ColorRGB* color)
	: WorldObject(scene, id, objectName, color)
{
	size(_INIT_SIZE);
}


CatObject::~CatObject()
{
}

void CatObject::Display() {
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
	DrawCat();

	glDisable(GL_LIGHTING);
	glPopMatrix();
}

void CatObject::DrawCat() {
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

	red = (color->x + 0.38f) / 2.f;
	gre = (color->y + 0.15f) / 2.f;
	blu = (color->z + 0.05f) / 2.f;

	/* Shoulder Joints */
	glPushMatrix();
	glTranslatef(-body_width / 2, -body_height / 7, 0);
	glColor3f(red, gre, blu);
	DrawSphere(joint_r, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(body_width / 2, -body_height / 7, 0);
	glColor3f(red, gre, blu);
	DrawSphere(joint_r, 5);
	glPopMatrix();

	/* Translate to the rear of the model to render the legs */
	glTranslatef(0.f, -body_length / 2.f, 0.f);

	// Legs
	glPushMatrix();
	DrawLeg(leg_length, leg_r, 0);
	glPopMatrix();

	glPushMatrix();
	DrawLeg(leg_length, leg_r, 1);
	glPopMatrix();

	/* Render another "leg" to be used as the tail */
	glTranslatef(body_width / 2.f, body_height, -body_width / 2.f);
	glRotatef(180.f, 0.f, 0.f, 1.f);
	glRotatef(45.f, 1.f, 0.f, 0.f);
	glPushMatrix();
	DrawLeg(leg_length, leg_r/2.f, 1);
	glPopMatrix();
	glRotatef(-45.f, 1.f, 0.f, 0.f);
	glRotatef(-180.f, 0.f, 0.f, 1.f);
	glTranslatef(-body_width / 2.f, -body_height, body_width / 2.f);

	/* Hip Joints */
	// Right
	glPushMatrix();
	glTranslatef(body_width / 2.f - leg_r / 2.f, 0.f, -body_height);
	glColor3f(red, gre, blu);
	DrawSphere(leg_r / 1.5f, 5);
	glPopMatrix();

	// Left
	glPushMatrix();
	glTranslatef(body_width / 2.f - leg_r / 2.f, 0.f, -body_height);
	glColor3f(red, gre, blu);
	DrawSphere(leg_r / 1.5f, 5);
	glPopMatrix();
}

void CatObject::DrawHead(float R) {
	/* This function draws the head of the model
	** A texture is applied to the head
	*/

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texId);
	
	glColor3f((color->x + 1) / 2.f, (color->y + 1) / 2.f, (color->z + 1) / 2.f);
	glRotatef(-90.f, 1.f, 0.f, 0.f);
	DrawSphere(R, 5);
	glRotatef(90.f, 1.f, 0.f, 0.f);

	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);

	/* Render the ears */
	float red, gre, blu;

	red = (color->x + 0.38f) / 2.f;
	gre = (color->y + 0.15f) / 2.f;
	blu = (color->z + 0.05f) / 2.f;

	glColor3f(red, gre, blu);
	
	glPushMatrix();
	glTranslatef(-R / 2.f, R, R / 4.f);
	glScalef(1.f, 2.f, 0.5f);
	glutSolidCube(R / 4.f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(R / 2.f, R, R / 4.f);
	glScalef(1.f, 2.f, 0.5f);
	glutSolidCube(R / 4.f);
	glPopMatrix();

	glPopMatrix();
}


void CatObject::DrawArm(float length, float r, int dir) {
	/* This function draws an arm of the model */
	float red, gre, blu;

	red = 0.8f * (color->x + 0.38f) / 2.f;
	gre = 0.8f * (color->y + 0.15f) / 2.f;
	blu = 0.8f * (color->z + 0.05f) / 2.f;

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
	}
	else  {
		// right arm
		// rotate 180 degrees around to flip the arm
		glRotatef(180.f, 0.f, 1.f, 0.f);
		mult = 1;
	}

	/* Drawing the upper arm */
	glTranslatef(0.f, -0.25f, 0.0f); 
	glRotatef(upper_angle, 1.0f, 0.f, 0.f);
	glTranslatef(-body_width / 2.f - arm_length / 8.f + arm_r / 2.f, -arm_length / 4.f, 0.f);
	glRotatef(-arm_angle, 0.f, 0.f, 1.f);

	glScalef(r, length / 2, r); // set scale of this part of the arm
	glutSolidCube(1.f);
	glScalef(1 / r, 2 / length, 1 / r); // reverse scaling

	glTranslatef(0.f, (-length / 4), 0.0f);
	DrawSphere(joint_r*1.2f, 3); // draw the arm joint

	/* Drawing the lower arm */
	glRotatef(mult * lower_angle, 1.0f, 0.f, 0.f);
	glTranslatef(0, (-length / 4.0f) + (joint_r / 2.0f), 0.0f);

	red = (color->x + 0.38f) / 2.f;
	gre = (color->y + 0.15f) / 2.f;
	blu = (color->z + 0.05f) / 2.f;

	glColor3f(red, gre, blu);
	glScalef(r, length / 2, r); // set scale of this part of the arm
	glutSolidCube(1.f); // draw the lower part of the arm

	glTranslatef(0.0f, 0.0f, 0.0f);

	glScalef(1 / r, 2 / length, 1 / r); // reverse scaling
}

void CatObject::DrawLeg(float length, float r, int dir) {
	/* This function draws a leg of the model */
	float red, gre, blu;

	red = 0.8f * (color->x + 0.38f) / 2.f;
	gre = 0.8f * (color->y + 0.15f) / 2.f;
	blu = 0.8f * (color->z + 0.05f) / 2.f;

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
	}
	else {
		// right leg
		// rotate 180 degrees around to flip the leg
		glRotatef(180.f, 0.f, 1.f, 0.f);
		mult = 1;
	}

	/* Drawing the upper leg */
	glTranslatef(-body_width / 2.f - arm_length / 8.f + arm_r / 2.f, 0.f, body_height * mult);
	glRotatef(-upper_angle, 1.0f, 0.f, 0.f);
	glRotatef(-leg_angle, 0.f, 0.f, 1.f);
	glScalef(r, length / 2, r); // set scale of this part of the leg
	glutSolidCube(1.f);
	glScalef(1 / r, 2 / length, 1 / r); // reverse scaling

	glTranslatef(0.f, -length / 4, 0.f);
	DrawSphere((float)r / sqrt(2.0f), 5); // draw the leg joint

	/* Drawing the lower arm */
	glRotatef(mult * lower_angle, 1.0f, 0.f, 0.f);
	glRotatef(leg_angle, 0.f, 0.f, 1.f);
	glTranslatef(0.f, -length / 4, 0.f);
	glScalef(r, length / 2, r); // set scale of this part of the leg

	red = (color->x + 0.38f) / 2.f;
	gre = (color->y + 0.15f) / 2.f;
	blu = (color->z + 0.05f) / 2.f;

	glColor3f(red, gre, blu);
	glutSolidCube(1.f); // draw the lower part of the leg

	glScalef(1 / r, 2 / length, 1 / r); // reverse scaling
}

void CatObject::DrawBody(float width, float length, float height) {
	/* This function draws the body of the model */
	float red, gre, blu;

	red = (color->x + 0.38f) / 2.f;
	gre = (color->y + 0.15f) / 2.f;
	blu = (color->z + 0.05f) / 2.f;

	glColor3f(red, gre, blu);
	glTranslatef(0.f, 0.f, -height / 2.f);
	glRotatef(-90.f, 1.f, 0.f, 0.f);
	glScalef(width, height, length);
	glutSolidCube(1.f);

}

void CatObject::DrawSphere(float R, int depth) {
	/* This function creates and draws a textured sphere 
	** that is used as the head of the model
	*/
	GLUquadricObj *sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);

	gluSphere(sphere, R, 10, 10);
}

void CatObject::Update(const double& deltaTime) {
	/* This function is called whenever the scene is updated
	** deltaTime refers to the change in time since the previous update
	** In this function, I set the angles and position of the model to
	** animate it
	*/
	
	/* If the arm angle has reached its upper or lower limit, change the direction */
	if (upper_arm_angle <= upper_limb_min_angle || upper_arm_angle >= upper_limb_max_angle) {
		animation_dir *= -1.f;
	}

	/* Create values that remain only in scope for this function */
	float low_angle_min = lower_limb_min_angle;
	float low_angle_max = lower_limb_max_angle;

	/* Increment the angles based on the predefined speed, and calculated direction */
	upper_arm_angle += animation_dir * animation_speed;
	lower_arm_angle += animation_dir * animation_speed;

	/* Here I check the bounds of the lower angle, this is used to give the 
	** walking animation a more realistic appearance
	*/
	if (lower_arm_angle <= low_angle_min) {
		lower_arm_angle = low_angle_min;
	}
	else if (lower_arm_angle >= low_angle_max) {
		lower_arm_angle = low_angle_max;
	}

	/* Here we randomly determine values for whether the cat should move this update
	** and if so, what direction
	*/

	/* This determines how long a walk cycle lasts for */
	bool change = rand() % 32 == 0;
	if (change) {
		up = false;
		dn = false;
		lf = false;
		rt = false;
	}

	/* This determines which direction a walk goes in
	** Each option has a 1/256 chance to occur
	*/
	int dir = rand() % 256; // choose direction, up lf dn rt uplf uprt dnlf dnrt
	switch (dir)
	{
	case 0: // up
		up = true;
		break;
	case 1: // lf
		lf = true;
		break;
	case 2: // dn
		dn = true;
		break;
	case 3: // rt
		rt = true;
		break;
	case 4: { // up+lf
		up = true;
		lf = true;
		break;
	}
	case 5: { // up+rt
		up = true;
		rt = true;
		break;
	}
	case 6: { // dn+lf
		dn = true;
		lf = true;
		break;
	}
	case 7: { // dn+rt
		dn = true;
		rt = true;
		break;
	}
	default:
		break;
	}

	/* Update the position and rotation based on the walk direction 
	** This also checks that the cat is within the bounds of the scene
	*/
	float velocity = walk_speed;
	if (up) {
		if (pos[2] - velocity > _ZBOUND_MIN) pos[2] -= velocity;
		rotation[1] = 180.f;
	}
	if (dn) {
		if (pos[2] + velocity < _ZBOUND_MAX * 2) pos[2] += velocity;
		rotation[1] = 0.f;
	}
	if (lf) {
		if (pos[0] - velocity > _XBOUND_MIN) pos[0] -= velocity;
		rotation[1] = 270.f;
	}
	if (rt) {
		if (pos[0] + velocity < _XBOUND_MAX - 180) pos[0] += velocity;
		rotation[1] = 90.f;
	}

	/* Diagonal angles */
	if (up && rt) {
		rotation[1] = 135.f;
	}
	if (up && lf) {
		rotation[1] = 215.f;
	}
	if (dn && rt) {
		rotation[1] = 45.f;
	}
	if (dn && lf) {
		rotation[1] = 315.f;
	}

	/* Reset the walking state */
	walking = false;

	/* If the cat has moved, and values do not conflict
	** e.g. walking both left and right at the same time
	** Then set the walking state to true
	*/
	if (lf || rt) {
		if (lf != rt) {
			walking = true;
		}
	}
	else if (up || dn) {
		if (up != dn) {
			walking = true;
		}
	}

	/* If the walking state is false, reset the angles of the limbs */
	if (!(walking)) {
		upper_arm_angle = 0.f;
		lower_arm_angle = 0.f;
	}

}