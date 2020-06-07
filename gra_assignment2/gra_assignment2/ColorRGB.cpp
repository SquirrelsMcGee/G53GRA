#include "ColorRGB.h"

/*
	Class that extends Vertex
	Done to remove ambiguity from later statements
*/

ColorRGB::ColorRGB()
{
	x = 0;
	y = 0;
	z = 0;

}

ColorRGB::ColorRGB(float f1, float f2, float f3) {
	x = f1;
	y = f2;
	z = f3;
}


ColorRGB::~ColorRGB()
{
}