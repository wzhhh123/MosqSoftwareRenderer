#pragma once

#include "public.h"

#include "glm.hpp"
class Vertex {
public:
		float GetX();
		float GetY();
		float GetZ();

		Vertex(float, float, float, glm::vec4 color);
		Vertex(glm::vec4 pos, glm::vec4 color);


		glm::vec4 getTexCoord();
		Vertex transform(glm::mat4 transform);
		Vertex perspectiveDivide();
		float triangleAreaTimesTwo(Vertex a, Vertex b);
private:
		glm::vec4 _pos;
		glm::vec4 _texCoord;
};