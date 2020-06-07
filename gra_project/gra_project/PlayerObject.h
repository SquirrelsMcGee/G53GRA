#pragma once
#include "WorldObject.h"
#include "Functions.h"

/* This is a class that is used to render a hierarchical model of a Person 
** to the screen
*/
class PlayerObject :
	public WorldObject
{
public:
	PlayerObject(MyScene* scene, int id, std::string objectName, ColorRGB* color);
	~PlayerObject();

	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);
	
	/* Texture ID */
	int texId = 0;

	/* This variable is used to check if the player is in an 
	** interaction state 
	*/
	bool interacting = false;

private:
	/*This function is used to begin rendering of the model */
	void DrawPlayer();

	/* These functions are used to draw different parts of the model */
	void DrawHead(float R);
	void DrawArm(float length, float r, int dir);
	void DrawLeg(float length, float r, int dir);
	void DrawBody(float width, float length, float height);
	void DrawSphere(float r, int depth);

	/* A string used for texuring the face of the model */
	std::string _tex_path = "../Texture/player_face.bmp";

	/* These variables are used to define the various attributes
	** that define the shape of the model
	*/
	float R = 1.2f;  // head
	float body_width = 1.5f;
	float body_length = 0.5f;
	float body_height = 2.5f;
	float arm_length = 3.f;
	float arm_r = 0.3f;
	float leg_r = 0.5f;
	float leg_length = 4.f;
	float joint_r = 0.2f;

	/* These variables are used to define the angles the define the model
	** and the upper and lower limits by which they are allowed to animate
	**
	** The angles used for the arms are also used to animate the legs as well
	*/
	float arm_angle = 10.0f;
	float leg_angle = 0.0f;

	float upper_arm_angle = 0.0f;
	float lower_arm_angle = 0.0f;

	float lower_limb_min_angle = 0.0f;
	float lower_limb_max_angle = 45.0f;

	float upper_limb_min_angle = -45.0f;
	float upper_limb_max_angle = 45.0f;

	/* These values used by Update() to change how far the limbs can move without 
	** affecting the original values
	*/

	float low_angle_min = lower_limb_min_angle;
	float low_angle_max = lower_limb_max_angle;
	float upper_angle_min = upper_limb_min_angle;
	float upper_angle_max = upper_limb_max_angle;

	/* These variables are used for animating the model, defining the speed
	** at which various parts animate, and how fast the model moves around
	** the scene
	*/
	float animation_dir = 1;
	float speed = 4.f;

	/* These variables are used to determine if the object is in a walking state
	** and what direction the model is walking in
	*/
	bool walking = false;
	GLboolean up = false, dn = false, lf = false, rt = false;
	float prevRot = 0.f;

	/* These variables are used to define the light characteristics of the model */
	GLfloat mat_ambient[4] = { 0.f, 0.f, 0.f, 1.f };
	GLfloat mat_diffuse[4] = { 0.f, 0.f, 0.f, 1.f };
	GLfloat mat_specular[4] = { 0.f, 0.f, 0.f, 1.f };
	GLfloat mat_shininess[1] = { 128 }; // 0-128

	/* These variables are used for certain timed animations
	** Currently they are used to keep the player in an interacting state
	*/
	float timeDelay = 1.0f; // seconds for specific animations to last
	float timeCount = 0.0f;  // duration counter for timeDelay

	/* These variables used as flags for keypresses */
	GLboolean _iKey, _jKey, _kKey, _lKey, _oKey, _uKey;
	GLboolean _plusKey, _minusKey, _upKey, _downKey, _leftKey, _rightKey, _wKey, _sKey, _aKey, _dKey, _fKey;
	GLboolean _flagReset, _shiftKey;
};

