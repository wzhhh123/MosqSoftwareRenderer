#pragma once

#include "public.h"

#include "glm.hpp"
class Vertex {
public:
		float GetX();
		float GetY();
		float GetZ();

		Vertex(float, float, float);

		float triangleArea(Vertex a, Vertex b);
private:
		glm::vec3 _pos;
};