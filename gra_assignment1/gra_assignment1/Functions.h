#pragma once

#define _INIT_SIZE 10.0f
#define _DEF_X 500.0f
#define _DEF_Z -500.0f

#include <iostream>

#include "Vertex.h"

#include "Framework\Interface\DisplayableObject.h"
#include "Framework\Interface\Animation.h"
#include "Framework\Interface\Input.h"


using namespace std;

float FloatNormalise(float f1, float min, float max);
Vertex * Centroid3(Vertex *v1, Vertex *v2, Vertex *v3);