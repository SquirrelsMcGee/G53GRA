#include "Functions.h"

float FloatNormalise(float in, float min, float max) {
	// returns a normalised floating point value in the range 0-1 from a given range
	return (in - min) /	(max-min);
}

Vertex * Centroid3(Vertex *a, Vertex *b, Vertex *c) {
	// returns the centroid vertex of a triplet of 3D vertices
	try {
		return new Vertex(
			(a->x + b->x + c->x) / 3.0,
			(a->y + b->y + c->y) / 3.0,
			(a->z + b->z + c->z) / 3.0
		);
	}
	catch (...) {
		cout << "Exception caught at Centroid3" << endl;
	}

}
