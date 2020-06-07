#include "MyScene.h"



int main(int argc, char* argv[])
{
	// seed random numbers
	srand(12903823);

	// Create new instance of MyScene - the OpenGL context on which your coursework is built
	MyScene *scene = NULL;
	scene = new MyScene(argc, argv, "A scene by James Steer - psyjbs", static_cast<const int>(1280), static_cast<const int>(720));
	// Begin the main GL loop
	scene->Run();

	// On exit, clean up and return success (0x0)
	delete scene;

	return 0;
}