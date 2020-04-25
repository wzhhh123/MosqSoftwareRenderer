#pragma once

#include "public.h"
#include <vector>

class Gradients {
public:
		Gradients(Vertex minYVert, Vertex midYVert, Vertex maxYVert);

		glm::vec4 getTexCoord(int loc);
		glm::vec4 getTexCoordXStep();
		glm::vec4 getTexCoordYStep();

		Mosq_Float getOneOverZ(int loc);
		Mosq_Float getOneOverZXStep();
		Mosq_Float getOneOverZYStep();

		Mosq_Float getDepth(int loc);
		Mosq_Float getDepthXStep();
		Mosq_Float getDepthYStep();


private:

		std::vector<glm::vec4>_texCoord;
		glm::vec4 _texCoordXStep;
		glm::vec4 _texCoordYStep;

		std::vector<Mosq_Float>_oneOverZ;
		Mosq_Float _oneOverZXStep;
		Mosq_Float _oneOverZYStep;

		std::vector<Mosq_Float> _depth;
		Mosq_Float _depthXStep;
		Mosq_Float _depthYStep;

};