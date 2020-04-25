

#include "vertex.h"

Mosq_Float Vertex::GetX() {
		return _pos.x;
}

Mosq_Float Vertex::GetY() {
		return _pos.y;
}

Mosq_Float Vertex::GetZ() {
		return _pos.z;
}

Mosq_Float Vertex::GetW() {
		return _pos.w;
}

Vertex::Vertex() {
		
}

Vertex Vertex::lerp(Vertex to, Mosq_Float t) {
		Vertex res(_pos*(1 - t) + t * to._pos, _texCoord*(1 - t) + t * to._texCoord);
		return res;
}


Vertex::Vertex(Mosq_Float x, Mosq_Float y, Mosq_Float z, glm::vec4 texCoord) {
		_pos.x = x;
		_pos.y = y;
		_pos.z = z;
		_pos.w = 1;
		_texCoord = texCoord;
}

Vertex::Vertex(Mosq_Float x, Mosq_Float y , Mosq_Float z, Mosq_Float w, glm::vec4 texCoord) {
		_pos.x = x;
		_pos.y = y;
		_pos.z = z;
		_pos.w = w;
		_texCoord = texCoord;
}



Vertex::Vertex(glm::vec4 pos, glm::vec4 texCoord) {
		_pos = pos;
		_texCoord = texCoord;
}


glm::vec4 Vertex::getTexCoord() { return _texCoord; }

Vertex Vertex::transform(glm::mat4 transform) {
		auto val = Vertex(transform * _pos, _texCoord);
		return val;
}


//透视除法的时候保留w的值，方便计算
Vertex Vertex::perspectiveDivide() {
		return Vertex(_pos.x / _pos.w, _pos.y / _pos.w, _pos.z / _pos.w, _pos.w, _texCoord);
}

Mosq_Float Vertex::triangleAreaTimesTwo(Vertex a, Vertex b) {

		Mosq_Float  x1 = a.GetX() - _pos.x;
		Mosq_Float y1 = a.GetY() - _pos.y;

		Mosq_Float x2 = b.GetX() - _pos.x;
		Mosq_Float y2 = b.GetY() - _pos.y;

		return x1 * y2 - x2 * y1;
}


 