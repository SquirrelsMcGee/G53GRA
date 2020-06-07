#include "Functions.h"

float FloatNormalise(float in, float min, float max) {
	// returns a normalised floating point value in the range 0-1 from a given range
	return (in - min) /	(max-min);
}

Vertex * Centroid3(Vertex *a, Vertex *b, Vertex *c) {
	// returns the centroid vertex of a triplet of 3D vertices
	try {
		return new Vertex(
			(a->x + b->x + c->x) / 3.0f,
			(a->y + b->y + c->y) / 3.0f,
			(a->z + b->z + c->z) / 3.0f
		);
	}
	catch (...) {
		cout << "Exception caught at Centroid3" << endl;
		return nullptr;
	}

}

Vertex * CrossProduct(Vertex *a, Vertex *b) {
	// returns the cross product (/normal) of two 3x1 vertices
	try {
		return new Vertex(
			((a->y)*(b->z)) - ((b->y)*(a->z)),
			((a->z)*(b->x)) - ((b->z)*(a->x)),
			((a->x)*(b->y)) - ((b->x)*(a->y))
		);
	}
	catch (...) {
		cout << "Exception caught at CrossProduct" << endl;
		return nullptr;
	}
}