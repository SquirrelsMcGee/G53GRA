#pragma once
#include "WorldObject.h"
#include "Functions.h"

class RobotObject :
	public WorldObject
{
public:
	RobotObject(MyScene* scene, int id, std::string objectName, ColorRGB* color);
	~RobotObject();

	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);


	void DrawHead(float R);
	void DrawArm(float length, float r, int dir);
	void DrawLeg(float length, float r, int dir);
	void DrawBody(float width, float length, float height);
	void DrawSphere(float r, int depth);
	void Subdivide(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], int depth, float R);
	void normalize(GLfloat v[3], float R);
	void DrawJoint(float h, float r);

private:
	void DrawRobot();

	GLboolean _iKey, _jKey, _kKey, _lKey, _oKey, _uKey;
	GLboolean _plusKey, _minusKey, _upKey, _downKey, _leftKey, _rightKey;
	GLboolean _flagReset;

	float R = 0.8f;  // head
	float body_width = 1.5f;
	float body_length = 0.5f;
	float body_height = 2.5f;
	float arm_length = 2.f;
	float arm_r = 0.3f;
	float leg_r = 0.5f;
	float leg_length = 3.f;
	float joint_r = 0.3f;
};

