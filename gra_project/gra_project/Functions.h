#pragma once
/* This file is a multi-purpose header 
** It contains several pre-processor definitions as well as many 
** included files that would otherwise be repeated
*/
#define _INIT_SIZE 10.0f
#define _DEF_X 500.0f
#define _DEF_Z -500.0f

#define PI 3.14159265
#define _USE_MATH_DEFINES

// Outer Collision bounds
#define _XBOUND_MAX 70.f
#define _XBOUND_MIN -480.f
#define _ZBOUND_MAX 320.f
#define _ZBOUND_MIN 100.f

#include <iostream>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <GL/freeglut.h>

#include "Vertex.h"
#include "Triangle.h"
#include "Quad.h"
#include "ColorRGB.h"

#include "Framework\Interface\DisplayableObject.h"
#include "Framework\Interface\Animation.h"
#include "Framework\Interface\Input.h"
