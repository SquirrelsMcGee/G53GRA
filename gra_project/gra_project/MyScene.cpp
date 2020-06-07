#include "MyScene.h"

/* Because the following classes utilise the MyScene class
** and thus include MyScene.h, the header file cannot contain 
** these dependencies
** Therefore in MyScene.h empty class definitions are created
** and the actual classes are included here
*/
#include "WorldObject.h"
#include "SquareObject.h"
#include "PlayerObject.h"
#include "CatObject.h"
#include "WallObject.h"
#include "ModelObject.h"
#include "LightObject.h"
#include "Skybox.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{
	// Initiate MyScene
	objectsList = new std::vector<WorldObject*>;
	angles = new std::vector<double>;
	lights = new std::vector<LightObject*>;
	controller = new XInputController(0);
	if (!controller->IsConnected()) {
		std::cout << "XINPUT: Controller Not Found" << std::endl;
	}
}


MyScene::~MyScene()
{
}

XInputController * MyScene::GetController() {
	return controller;
}

void MyScene::Initialise()
{
	/* In this function, I create all of the objects that are going to be
	** placed into the scene, I also set their attributes here also
	** These include colour, position, scale, orientation, texture etc.
	*/

	glutSetCursor(GLUT_CURSOR_NONE);

	/* Define colours that are repeatedly used by WorldObjects */
	ColorRGB * playerColour;
	ColorRGB * litColour = new ColorRGB(1.f, 1.f, 1.f); // brightly lit colour
	ColorRGB * dimmedColour = new ColorRGB(.8f, .8f, .8f); // mostly lit colour
	ColorRGB * wallColour = new ColorRGB(.2f, .2f, .2f);
	playerColour = wallColour;

	/* Create the player and NPC objects */
	PlayerObject *player1 = new PlayerObject(this, 0, "PlayerObject", playerColour);
	CatObject *cat1 = new CatObject(this, 1, "CatObject", wallColour);
	
	/* Create the walls that are placed at the rear of the scene */
	WallObject *wall1 = new WallObject(this, 10, "WallObject", wallColour, new Vertex(x_dist, y_dist, z_dist - (building_depth / 2.f)), false, "wall");
	WallObject *wall2 = new WallObject(this, 11, "WallObject", wallColour, new Vertex(-building_width - 10, y_dist, (-building_depth / 2.f) + 50), false, "wall");
	WallObject *wall3 = new WallObject(this, 12, "WallObject", wallColour, new Vertex(x_dist - building_depth * 1.5f, y_dist, (-building_depth / 2.f) + 50), false, "wall");
	WallObject *wall4 = new WallObject(this, 13, "WallObject", wallColour, new Vertex(x_dist, y_dist, 2 * building_depth + 50), false, "wall");
	WallObject *wall5 = new WallObject(this, 14, "WallObject", wallColour, new Vertex(x_dist - building_depth, y_dist, 2 * building_depth + 50), false, "wall");
	WallObject *wall6 = new WallObject(this, 15, "WallObject", wallColour, new Vertex(x_dist - building_depth, y_dist, z_dist - 150), false, "fence");
	/* Wall6 is a transparent mesh and is added to the scene last */
	
	/* Create the floor tiles that are places at the bottom of the scene */
	WallObject *floor1 = new WallObject(this, 20, "WallObject", dimmedColour, new Vertex(x_dist, y_dist - 110, z_dist - 10), true, "floor");
	WallObject *floor2 = new WallObject(this, 21, "WallObject", dimmedColour, new Vertex(x_dist - building_depth, y_dist - 110, z_dist - 10), true, "floor");
	WallObject *floor3 = new WallObject(this, 22, "WallObject", dimmedColour, new Vertex(x_dist, y_dist - 110, z_dist - 10 + building_depth), true, "floor");
	WallObject *floor4 = new WallObject(this, 23, "WallObject", dimmedColour, new Vertex(x_dist - building_depth, y_dist - 110, z_dist - 10 + building_depth), true, "floor");
	WallObject *floor5 = new WallObject(this, 24, "WallObject", dimmedColour, new Vertex(x_dist- building_depth, y_dist - 110, z_dist - 10 - building_depth), true, "floor");
	WallObject *floor6 = new WallObject(this, 25, "WallObject", dimmedColour, new Vertex(x_dist, y_dist - 110, z_dist - 10 - 2* building_depth), true, "floor");
	WallObject *floor7 = new WallObject(this, 26, "WallObject", dimmedColour, new Vertex(x_dist - building_depth, y_dist - 110, z_dist - 10 - 2 * building_depth), true, "floor");
	WallObject *floor8 = new WallObject(this, 27, "WallObject", dimmedColour, new Vertex(x_dist - 2 * building_depth, y_dist - 110, z_dist - 10 - 2 * building_depth), true, "floor");

	/* Create the buildings that surround the player */
	/* These use a textured .obj file */
	ModelObject *building1 = new ModelObject(this, 30, "BuildingObject", wallColour, "cube", GL_CW);
	ModelObject *building2 = new ModelObject(this, 31, "BuildingObject", wallColour, "cube", GL_CW);
	ModelObject *building3 = new ModelObject(this, 32, "BuildingObject", litColour, "cube", GL_CW);
	ModelObject *building4 = new ModelObject(this, 33, "BuildingObject", litColour, "cube", GL_CW);
	ModelObject *building5 = new ModelObject(this, 34, "BuildingObject", litColour, "cube", GL_CW);
	ModelObject *building6 = new ModelObject(this, 35, "BuildingObject", wallColour, "cube", GL_CW);
	ModelObject *building7 = new ModelObject(this, 36, "BuildingObject", wallColour, "cube", GL_CW);

	
	/* Building 3, 4 & 5 are placed at the back of the scene and are lit and
	** textured differently 
	*/
	building3->_texId = this->GetTexture("../Texture/shop_night.bmp");
	building4->_texId = this->GetTexture("../Texture/shop_night.bmp");
	building5->_texId = this->GetTexture("../Texture/shop_night.bmp");

	/* Create ModelObject that is able to parse and load wavefront *.obj files */
	ModelObject *campfire = new ModelObject(this, 40, "ModelObject", dimmedColour, "campfire", GL_CCW);
	ModelObject *carModel = new ModelObject(this, 41, "ModelObject", dimmedColour, "car", GL_CCW);
	ModelObject *binModel1 = new ModelObject(this, 42, "ModelObject", wallColour, "garbage", GL_CCW);
	ModelObject *sleepBag = new ModelObject(this, 43, "ModelObject", wallColour, "sleeping_bag", GL_CCW);

	/* Create square planes to be used for rendering the flame textures onto 
	** SquareObject supports animated textures by loading multiple *.bmp files
	*/
	SquareObject *flame1 = new SquareObject(this, 51, "SquareObject", litColour, "flames/flame", 8, 0.1f);
	SquareObject *flame2 = new SquareObject(this, 52, "SquareObject", litColour, "flames/flame", 8, 0.1f);

	/* Create lights to be placed into the scene, the light id is the last argument 
	** given to the constructor
	*/
	LightObject *light1 = new LightObject(this, 100, "LightObject", new ColorRGB(1.0f, 1.0f, 1.0f), 0);
	LightObject *light2 = new LightObject(this, 101, "LightObject", new ColorRGB(1.0f, 0.5f, 0.4f), 1);

	/* Create the skybox and give MyScene a reference to it */
	Skybox *skybox1 = new Skybox(this, 200, "Skybox", litColour);
	skybox = skybox1;

	/* In this section, I set arbitrary values to create the scene
	** These include:
	** position, scale, orientation, alpha, light ambient, rendering both sides
	** There are some commonly used variables, such as z_dist, y_dist & x_dist,
	** these are used to position the scene, and give offsets to objects it is
	** required
	** I have grouped them into similar groups
	**/

	player1->setPosition(new Vertex(0.0f, 0.0f, z_dist));
	cat1->setPosition(new Vertex(x_dist*5, -y_dist, z_dist));
	cat1->setScale(new Vertex(8.f, 8.f, 8.f));
	player1->setLightColor(new ColorRGB(1.0f, 0.5f, 0.4f));

	wall1->setOrientation(new Vertex(0.0f, 0.0f, 0.0f));
	wall2->setOrientation(new Vertex(0.0f, -90.0f, 0.0f));
	wall3->setOrientation(new Vertex(0.0f, 90.0f, 0.0f));
	wall4->setOrientation(new Vertex(0.0f, -180.0f, 0.0f));
	wall5->setOrientation(new Vertex(0.0f, -180.0f, 0.0f));
	wall6->setOrientation(new Vertex(0.0f, 0.0f, 0.0f));
	wall6->alpha = 1.0f;
	
	floor1->setOrientation(new Vertex(-90.0f, 0.0f, 0.0f));
	floor2->setOrientation(new Vertex(-90.0f, 0.0f, 0.0f));
	floor3->setOrientation(new Vertex(-90.0f, 0.0f, 0.0f));
	floor4->setOrientation(new Vertex(-90.0f, 0.0f, 0.0f));
	floor5->setOrientation(new Vertex(-90.0f, 0.0f, 0.0f));
	floor6->setOrientation(new Vertex(-90.0f, 0.0f, 0.0f));
	floor7->setOrientation(new Vertex(-90.0f, 0.0f, 0.0f));
	floor8->setOrientation(new Vertex(-90.0f, 0.0f, 0.0f));

	building1->setPosition(new Vertex((building_width - 10), (building_width - 10), z_dist));
	building2->setPosition(new Vertex((building_width - 10), (building_width - 10), z_dist + building_depth));
	building3->setPosition(new Vertex(x_dist - building_depth, (building_width /2.f) - 60, -2 * building_depth));
	building4->setPosition(new Vertex(x_dist - 2 * building_depth, (building_width / 2.f) - 60, -2 * building_depth));
	building5->setPosition(new Vertex(x_dist, (building_width / 2.f) - 60, -2 * building_depth));
	building6->setPosition(new Vertex(-(2 * building_depth) - 10, (building_width - 10), z_dist));
	building7->setPosition(new Vertex(-(2 * building_depth) - 10, (building_width - 10), z_dist + building_depth));
	building1->setScale(new Vertex(building_width, 500, building_depth));
	building2->setScale(new Vertex(building_width, 500, building_depth));
	building3->setScale(new Vertex(building_depth, 200, building_width / 2.f));
	building4->setScale(new Vertex(building_depth, 200, building_width / 2.f));
	building5->setScale(new Vertex(building_depth, 200, building_width / 2.f));
	building6->setScale(new Vertex(building_width, 500, building_depth));
	building7->setScale(new Vertex(building_width, 500, building_depth));
	building3->setOrientation(new Vertex(0, -90, 0));
	building4->setOrientation(new Vertex(0, -90, 0));
	building5->setOrientation(new Vertex(0, -90, 0));

	campfire->setPosition(new Vertex(x_dist, y_dist - 110, z_dist));
	carModel->setPosition(new Vertex(x_dist - building_depth, y_dist - 110, z_dist - 2 * building_depth));
	binModel1->setPosition(new Vertex(-x_dist, y_dist - 115, z_dist));
	sleepBag->setPosition(new Vertex(x_dist*2.5f, y_dist - 105, z_dist));
	campfire->setScale(new Vertex(8, 8, 8));
	carModel->setScale(new Vertex(30, 30, 30));
	sleepBag->setScale(new Vertex(10, 10, 10));
	binModel1->setScale(new Vertex(10, 10, 10));
	campfire->setOrientation(new Vertex(0, 0, 0));
	binModel1->setOrientation(new Vertex(0, 180, 0));
	campfire->setLightColor(new ColorRGB(1.0f, 0.5f, 0.4f));

	flame1->setPosition(new Vertex(x_dist - 5, -y_dist, z_dist));
	flame2->setPosition(new Vertex(x_dist - 5, -y_dist, z_dist));
	flame1->setOrientation(new Vertex(0, 0, 0));
	flame2->setOrientation(new Vertex(0, -90, 0));
	flame1->setScale(new Vertex(25, 50, 1));
	flame2->setScale(new Vertex(25, 50, 1));
	flame1->renderBothSides = true;
	flame2->renderBothSides = true;

	light1->setPosition(new Vertex(x_dist - building_depth, y_dist, z_dist - 2 * building_depth));
	light2->setPosition(new Vertex(x_dist, y_dist - 100, z_dist));
	light2->animation = "flame";

	skybox1->setPosition(new Vertex(0, 0.0f, z_dist));
	skybox1->setScale(new Vertex(2000, 2000, 2000));

	/* These are enabled later */
	flame1->DisableRendering();
	flame2->DisableRendering();
	light2->DisableRendering();

	/* 
	** Add objects to scene, the order added determines the order in which
	** they are rendered 
	** Recommended to render transparent objects at the end, so that the faces
	** behind them are not culled
	*/
	AddObject(skybox1);
	AddObject(light1);
	AddObject(light2); // To add interactivity to the scene, we add this later

	AddObject(player1);
	AddObject(cat1);

	AddObject(wall1);
	AddObject(wall2);
	AddObject(wall3);
	AddObject(wall4);
	AddObject(wall5);

	AddObject(floor1);
	AddObject(floor2);
	AddObject(floor3);
	AddObject(floor4);
	AddObject(floor5);
	AddObject(floor6);
	AddObject(floor7);
	AddObject(floor8);

	AddObject(building1);
	AddObject(building2);
	AddObject(building3);
	AddObject(building4);
	AddObject(building5);
	AddObject(building6);
	AddObject(building7);

	AddObject(campfire);
	AddObject(carModel);
	AddObject(binModel1);
	AddObject(sleepBag);
	
	// Render transparent objects after
	AddObject(flame1);
	AddObject(flame2);
	AddObject(wall6);
	/* wall6 is rendered at the end because it has transparency
	** If it was rendered before another object, face culling would effectively
	** remove the "occluded" part of the other object, despite logically being
	** visible
	*/

	/* Create references to certain WorldObjects for later use */
	this->player = player1;
	this->light2 = light2;
	this->flame1 = flame1;
	this->flame2 = flame2;
	this->campfire = campfire;
	
}

void MyScene::AddObject(WorldObject *obj) {
	/* Add objects to scene, and also to an internal vector of WorldObjects,
	** This is used so WorldObjects can determine the type of other WorldObjects
	** by accessing their objectName attribute
	*/
	objectsList->push_back(obj);
	AddObjectToScene(obj);
}

void MyScene::Projection()
{
	/* Create the projection used by the application */
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 50000.0);
}

void MyScene::Update(const double& deltaTime)
{
	/* Overloaded update function to add extra functionality, including:
	** Moving the camera based on the player movement
	** Adding new objects after the initialisation
	*/

	/* Get the position of the player and update the positions of the camera
	** and skybox accordingly 
	** Note that in the camera class I disabled resetting the position, as well as movement since 
	** this section deprecates those parts
	*/
	float *playerPos = player->position();
	float cameraPos[3] = { playerPos[0], playerPos[1], playerPos[2] };
	cameraPos[1] += 20;
	cameraPos[2] += 200;
	if (cameraPos[2] > _ZBOUND_MAX * 2) cameraPos[2] = _ZBOUND_MAX * 2;
	GetCamera()->SetEyePosition(cameraPos[0], cameraPos[1], cameraPos[2]);
	
	skybox->setPosition(new Vertex(cameraPos[0], cameraPos[1] - 500, cameraPos[2] + 200));

	/* This is a simple flag system for scene progression, here we have a single
	** flag that is used to check if the campfire has been lit or not
	** If the player is in an interacting state, and the flag for a lit campfire
	** is false, then we check if the player is nearby the campfire, and if they
	** are, "light" it by enabling the light and flames, the campfire is "put out"
	** by disabling them
	*/
	if (player->interacting) {
		if (flags[0] == false && flags[1] == false) {
			if (checkDistance(x_dist, z_dist, -x_dist * 1.1f)) {
				campfire->_texId = this->GetTexture("../Texture/campfire_lit.bmp");
				light2->EnableRendering();
				flame1->EnableRendering();
				flame2->EnableRendering();
				flags[1] = true;
			}
		}
		else if (flags[0] == false && flags[1] == true) {
			if (checkDistance(x_dist, z_dist, -x_dist * 1.1f)) {
				campfire->_texId = this->GetTexture("../Texture/campfire_lit.bmp");

				light2->DisableRendering();
				flame1->DisableRendering();
				flame2->DisableRendering();
				flags[1] = false;
			}
		}
		flags[0] = true;
	}
	else {
		flags[0] = false;
	}

	/* This is a as-yet unused feature of the application that allows objects
	** to create new WorldObjects in real time
	** Attempting to add a new WorldObject during its update() function caused 
	** the program to crash due to changing the size of the objects vector in 
	** Scene, so we check before running the update function if any new objects
	** need to be added
	*/
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
	
	/* Call Scene::Update for updating on screen objects */
	Scene::Update(deltaTime);
}

bool MyScene::checkDistance(float x, float z, float r) {
	/* Function used to check if the player is near an interactable object
	/* (x,z) = the origin of the interactable object in the x,z planes
	/* r = the distance which the player can interact from
	*/
	float *position = player->position();
	bool xbound = (position[0] > x - r) && (position[0] < x + r);
	bool zbound = (position[2] > z - r) && (position[2] < z + r);
	return xbound && zbound;
}

void checkGLError()
{
	/* Function used to get and print GL errors */
	int e = 0;                      // Error count
	GLenum error = glGetError();    // Get first glError
	while (GL_NO_ERROR != error)    // Loop until no errors found
	{
		e++;
		printf("GL Error %i: %s\n", e, gluErrorString(error)); // Display error string
		error = glGetError();                                  // Get next glError
	}
}
