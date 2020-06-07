#include "MyScene.h"

#include "WorldObject.h"
#include "SquareObject.h"
#include "RobotObject.h"
#include "WallObject.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{
	objectsList = new std::vector<WorldObject*>;
	angles = new std::vector<double>;
}


MyScene::~MyScene()
{
}


void MyScene::Initialise()
{
	srand(10032193);

	/*squareCount = 10;
	for (int i = 0; i < squareCount; i++)
		AddObject(new SquareObject(this, i, "SquareObject", new ColorRGB((rand() % 255) / 255.0f, (rand() % 255) / 255.0f, (rand() % 255) / 255.0f)));

	std::sort(angles->begin(), angles->end(), std::greater<double>());
	for (size_t i = 0; i < angles->size(); ++i) {
		std::cout << angles->at(i) << std::endl;
	}*/
	RobotObject *robot = new RobotObject(this, 0, "RobotObject", new ColorRGB(1.f, 1.f, 1.f));
	AddObject(robot);

	WallObject *wall = new WallObject(this, 1, "WallObject", new ColorRGB(0.5f, 0.5f, 0.5f));
	AddObject(wall);
}

void MyScene::AddObject(WorldObject *obj) {
	objectsList->push_back(obj);
	AddObjectToScene(obj);
}

void MyScene::AddAngle(double theta) {
	angles->push_back(theta);
}

void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 50000.0);
}

void MyScene::Update(const double& deltaTime)
{
	WorldObject *tempObj;
	std::vector<WorldObject*> *tempList;
	
	// Go through each WorldObject looking for requests to add new objects to the scene
	for (size_t i = 0; i < objectsList->size(); ++i) {
		tempObj = objectsList->at(i);
		tempList = tempObj->newObjects;
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
