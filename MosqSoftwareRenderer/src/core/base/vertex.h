#pragma once

#include "public.h"

#include "glm.hpp"
class Vertex {
public:
		float GetX();
		float GetY();
		float GetZ();

		Vertex(float, float, float);
		Vertex(glm::vec4 pos);

		Vertex transform(glm::mat4 transform);
		Vertex perspectiveDivide();
		float triangleAreaTimesTwo(Vertex a, Vertex b);
private:
		glm::vec4 _pos;
};