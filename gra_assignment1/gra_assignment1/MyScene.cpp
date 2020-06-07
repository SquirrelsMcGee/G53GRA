#include "MyScene.h"

#include "WorldObject.h"
#include "MySphere.h"
#include "Tetrahedron.h"
#include "Cube.h"
#include "ModelObject.h"
#include "FloorTile.h"

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
	//AddObject(sphere);

	tetra = new Tetrahedron(this);
	//AddObject(tetra);

	Cube *cube = new Cube(this);
	//AddObject(cube);

	string filename = "cottage";
	ModelObject *modelObject = new ModelObject(this, filename, new Vertex(.3f, .3f, .4f), GL_CCW);
	modelObject->setScale(new Vertex(10, 10, 10));
	modelObject->setPosition(new Vertex(0, -100, 0));
	modelObject->setOrientation(new Vertex(0, 0, 0));
	AddObject(modelObject);

	FloorTile * temp;
	int maxX = 20;
	int maxY = 20;
	for (int i = 0; i < maxX; i++) {
		for (int j = 0; j < maxY; j++) {
			temp = new FloorTile(this, new Vertex(-5 * maxX, -10, -5 * maxY), i, j, 10, 10);
			temp->color = new Vertex(rand() % 30 / 255.0, rand() % 30 / 255.0, rand() % ((255-180+1)+180) / 255.0);
			AddObject(temp);
		}
	}
			
	//FloorTile *tile = new FloorTile(this, new Vertex(0,-10,0), 0, 0, 10, 10);
	//tile->xWidth = 10;
	//tile->zHeight = 10;
	//AddObject(tile);


	xInput = new XInputController(xInputId);
	
	cout << "Instructions:\n";
	cout << "[A] Vibrate Left Only\n";
	cout << "[B] Vibrate Right Only\n";
	cout << "[X] Vibrate Both\n";
	cout << "[Y] Vibrate Neither\n";
	cout << "[BACK] Exit\n" << endl;

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
	XInputUpdate();

	WorldObject *tempObj;
	vector<WorldObject*> *tempList;

	// Go through each WorldObject looking for requests to add new objects to the scene
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

void MyScene::XInputUpdate() {
	
	SHORT threshold = 1000;
	if (!xInputEnabled) return;
	if (xInput->IsConnected()) {
		state = xInput->GetState();
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) xInput->Vibrate(65535, 0);
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) xInput->Vibrate(0, 65535);
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) xInput->Vibrate(65535, 65535);
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) xInput->Vibrate();
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) {}

		lx = state.Gamepad.sThumbLX;
		ly = state.Gamepad.sThumbLY;
		rx = state.Gamepad.sThumbRX;
		ry = state.Gamepad.sThumbRY;

		lt = state.Gamepad.bLeftTrigger;
		rt = state.Gamepad.bRightTrigger;

		if (lx < threshold && lx > -threshold) lx = 0;
		if (lx > -threshold && lx < threshold) lx = 0;
		if (ly < threshold && ly > -threshold) ly = 0;
		if (ly > -threshold && ly < threshold) ly = 0;

		if (rx < threshold && rx > -threshold) rx = 0;
		if (rx > -threshold && rx < threshold) rx = 0;
		if (ry < threshold && ry > -threshold) ry = 0;
		if (ry > -threshold && ry < threshold) ry = 0;

		int div = 256;
		lx /= div;
		ly /= div;
		rx /= div;
		ry /= div;

		if (abs(lx + ly + rx + ry) > 10) cout << lx << " " << ly << " " << rx << " " << ry << endl;
	}
	else {
		xInputId++;
		if (xInputId > 4) xInputId = 1;
		cout << "xinput not found, attempting id=" << xInputId << endl;
		delete xInput;
		xInput = new XInputController(xInputId);
	}
}