#pragma once

#include "public.h"
#include <vector>

class Gradients {
public:
		Gradients(Vertex minYVert, Vertex midYVert, Vertex maxYVert);

		glm::vec4 getTexCoord(int loc);
		glm::vec4 getTexCoordXStep();
		glm::vec4 getTexCoordYStep();

private:
		std::vector<glm::vec4>_texCoord;
		glm::vec4 _texCoordXStep;
		glm::vec4 _texCoordYStep;
};