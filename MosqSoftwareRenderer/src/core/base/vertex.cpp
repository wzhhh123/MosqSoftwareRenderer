

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


Vertex::Vertex(float x, float y, float z, glm::vec4 texCoord) {
		_pos.x = x;
		_pos.y = y;
		_pos.z = z;
		_pos.w = 1;
		_texCoord = texCoord;
}


Vertex::Vertex(glm::vec4 pos, glm::vec4 texCoord) {
		_pos = pos;
		_texCoord = texCoord;
}


glm::vec4 Vertex::getTexCoord() { return _texCoord; }

Vertex Vertex::transform(glm::mat4 transform) {
		auto pos = transform * _pos;
		auto val = Vertex(pos, _texCoord);
		return val;
}

Vertex Vertex::perspectiveDivide() {
		return Vertex(_pos / _pos.w, _texCoord);
}

float Vertex::triangleAreaTimesTwo(Vertex a, Vertex b) {

		float  x1 = a.GetX() - _pos.x;
		float y1 = a.GetY() - _pos.y;

		float x2 = b.GetX() - _pos.x;
		float y2 = b.GetY() - _pos.y;

		return x1 * y2 - x2 * y1;
}


 