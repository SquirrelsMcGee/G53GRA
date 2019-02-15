#include "MyScene.h"
/**
* Entry method, takes command line arguments and creates new Scene engine to render your G53GRA Coursework
*
* @see MyScene
*/
int main(int argc, char* argv[])
{
	// seed random numbers
	srand(1337);

	// Create new instance of MyScene - the OpenGL context on which your coursework is built
	MyScene *scene = NULL;
	scene = new MyScene(argc, argv, "G53GRA", static_cast<const int>(600), static_cast<const int>(400));

	// Begin the main GL loop
	scene->Run();

	// On exit, clean up and return success (0x0)
	delete scene;
	
	return 0;
}