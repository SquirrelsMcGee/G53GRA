#pragma once
#include "WorldObject.h"
#include "Functions.h"

/* This is a class that is used to render a hierarchical model of a Cat
** to the scene
** It is similar to RobotObject as the model is derived from it
*/
class CatObject :
	public WorldObject
{
public:
	CatObject(MyScene* scene, int id, std::string objectName, ColorRGB* color);
	~CatObject();

	void Display();
	void Update(const double& deltaTime);

	/* Texture ID */
	int texId = 0;

private:
	/*This function is used to begin rendering of the model */
	void DrawCat();
	
	/* These functions are used to draw different parts of the model */
	void DrawHead(float R);
	void DrawArm(float length, float r, int dir);
	void DrawLeg(float length, float r, int dir);
	void DrawBody(float width, float length, float height);
	void DrawSphere(float r, int depth);

	/* A string used for texuring the face of the model */
	std::string _tex_path = "../Texture/cat_face2.bmp";

	/* These variables are used to define the various attributes 
	** that define the shape of the model
	*/
	float R = 1.f;  // head
	float body_width = 1.5f;
	float body_length = 1.f;
	float body_height = 2.5f;
	float arm_length = 2.f;
	float arm_r = 0.5f;
	float leg_r = 0.5f;
	float leg_length = 2.f;
	float joint_r = 0.2f;

	/* These variables are used to define the angles the define the model
	** and the upper and lower limits by which they are allowed to animate
	** 
	** The angles used for the arms are also used to animate the legs as well
	*/
	float arm_angle = 0.0f;
	float leg_angle = 0.0f;

	float upper_arm_angle = 20.0f;
	float lower_arm_angle = 0.0f;

	float lower_limb_min_angle = 0.0f;
	float lower_limb_max_angle = 45.0f;

	float upper_limb_min_angle = -45.0f;
	float upper_limb_max_angle = 45.0f;

	/* These variables are used for animating the model, defining the speed
	** at which various parts animate, and how fast the model moves around
	** the scene
	*/
	float animation_dir = 1;
	float animation_speed = 4.f;
	float walk_speed = 2.f;

	/* These variables are used to determine if the object is in a walking state
	** and what direction the model is walking in
	*/
	float walking = false;
	GLboolean up = false, dn = false, lf = false, rt = false;

	/* These variables are used to define the light characteristics of the model */
	GLfloat mat_ambient[4] = { 0.f, 0.f, 0.f, 1.f };
	GLfloat mat_diffuse[4] = { 0.f, 0.f, 0.f, 1.f };
	GLfloat mat_specular[4] = { 0.f, 0.f, 0.f, 1.f };
	GLfloat mat_shininess[1] = { 128 }; // 0-128
};

