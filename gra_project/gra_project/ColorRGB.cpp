#include "ColorRGB.h"


ColorRGB::ColorRGB() {
	/* Default values set to 0.f */
	x = 0.f;
	y = 0.f;
	z = 0.f;

}

ColorRGB::ColorRGB(float f1, float f2, float f3) {
	/* Set RGB equal to the values given in order */
	x = f1;
	y = f2;
	z = f3;
}


ColorRGB::~ColorRGB()
{
}