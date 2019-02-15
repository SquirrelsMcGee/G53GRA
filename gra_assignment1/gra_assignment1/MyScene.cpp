#include "MyScene.h"

#include "WorldObject.h"
#include "MySphere.h"
#include "Tetrahedron.h"
#include "Cube.h"


MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{
}


MyScene::~MyScene()
{
}

void MyScene::Initialise()
{
	objectsList = new vector<WorldObject*>;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	MySphere *sphere = new MySphere(this);
	AddObject(sphere);

	tetra = new Tetrahedron(this);
	AddObject(tetra);

	Cube *cube = new Cube(this);
	AddObject(cube);

	/*
	xInput = new XInputController(1);
	
	std::cout << "Instructions:\n";
	std::cout << "[A] Vibrate Left Only\n";
	std::cout << "[B] Vibrate Right Only\n";
	std::cout << "[X] Vibrate Both\n";
	std::cout << "[Y] Vibrate Neither\n";
	std::cout << "[BACK] Exit\n";
	*/

}

void MyScene::AddObject(WorldObject *obj) {
	objectsList->push_back(obj);
	AddObjectToScene(obj);
}


void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 50000.0);
}

void MyScene::Update(const double& deltaTime)
{
	/*if (xInput->IsConnected()) {
		switch (xInput->GetState().Gamepad.wButtons) {
		case XINPUT_GAMEPAD_A: 
			xInput->Vibrate(65535, 0);
		}
	}
	else {
		cout << "xinput not found" << endl;
	}
	*/

	WorldObject *tempObj;
	vector<WorldObject*> *tempList;

	for (size_t i = 0; i < objectsList->size(); ++i) {
		tempObj = objectsList->at(i);
		tempList = tempObj->newObjs;
		for (size_t j = 0; j < tempList->size(); ++j) {
			AddObject(tempList->at(j));
			tempList->erase(tempList->begin() + j);
		}
	}

	// Call Scene::Update for updating on screen objects
	Scene::Update(deltaTime);
}

void checkGLError()
{
	int e = 0;                      // Error count
	GLenum error = glGetError();    // Get first glError
	while (GL_NO_ERROR != error)    // Loop until no errors found
	{
		e++;
		printf("GL Error %i: %s\n", e, gluErrorString(error)); // Display error string
		error = glGetError();                                  // Get next glError
	}
}