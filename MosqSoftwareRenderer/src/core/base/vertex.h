#pragma once

#include "public.h"

#include "glm.hpp"
class Vertex {
public:

		Mosq_Float GetX();
		Mosq_Float GetY();
		Mosq_Float GetZ();
		Mosq_Float GetW();

		Vertex(Mosq_Float, Mosq_Float, Mosq_Float, glm::vec4 color);
		Vertex(Mosq_Float, Mosq_Float, Mosq_Float, Mosq_Float, glm::vec4 color);
		Vertex(glm::vec4 pos, glm::vec4 color);
		Vertex();

		glm::vec4 getTexCoord();
		Vertex transform(glm::mat4 transform);
		//透视除法的时候保留w的值，方便计算
		Vertex perspectiveDivide();
		Mosq_Float triangleAreaTimesTwo(Vertex a, Vertex b);

private:
		glm::vec4 _pos;
		glm::vec4 _texCoord;
};