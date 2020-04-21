

#include "vertex.h"

float Vertex::GetX() {
		return _pos.x;
}

float Vertex::GetY() {
		return _pos.y;
}

float Vertex::GetZ() {
		return _pos.z;
}


Vertex::Vertex(float x, float y, float z) {
		_pos.x = x;
		_pos.y = y;
		_pos.z = z;
}



float Vertex::triangleArea(Vertex a, Vertex b) {

		float  x1 = a.GetX() - _pos.x;
		float y1 = a.GetY() - _pos.y;

		float x2 = b.GetX() - _pos.x;
		float y2 = b.GetY() - _pos.y;

		return x1 * y2 - x2 * y1;
}


 