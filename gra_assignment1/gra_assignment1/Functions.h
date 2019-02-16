#pragma once

#define _INIT_SIZE 10.0f
#define _DEF_X 500.0f
#define _DEF_Z -500.0f

#include <iostream>

#include "Vertex.h"
#include "Triangle.h"

#include "Framework\Interface\DisplayableObject.h"
#include "Framework\Interface\Animation.h"
#include "Framework\Interface\Input.h"


using namespace std;

/**
* Returns normalised values of given max/min within the range 0-1
* @ param f1 float
* @ param min float
* @ param max float
*/
float FloatNormalise(float f1, float min, float max);

/**
* Returns the centroid of 3 vertices
* @ param v1 Vertex*
* @ param v2 Vertex*
* @ param v3 Vertex*
*/
Vertex * Centroid3(Vertex *v1, Vertex *v2, Vertex *v3);

/**
* Returns the cross product of two vertices
* cross product = normal of plane as described by the 2 vertices
* @ param a Vertex*
* @ param b Vertex*
*/
Vertex * CrossProduct(Vertex *a, Vertex *b);