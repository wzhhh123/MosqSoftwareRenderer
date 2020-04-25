#pragma once


#include "public.h"

//三角形的一条边
class Edge {
public:
		Edge(std::shared_ptr<Gradients>gradients, Vertex start, Vertex end, int minYVertIndex);

		void step();
		int getYStart();
		int getYEnd();
		Mosq_Float getX();
		
		glm::vec4 getTexCoord();
		glm::vec4 getTexCoordStep();

		Mosq_Float getOneOverDepth();
		Mosq_Float getOneOverDepthStep();

		Mosq_Float getDepth();
		Mosq_Float getDepthStep();

private:
		Mosq_Float _curX;
		Mosq_Float _xStep;
		int _yStart;
		int _yEnd;
		
		glm::vec4 _texCoord;
		glm::vec4 _texCoordStep;

		Mosq_Float _oneOverDepth;
		Mosq_Float _oneOverDepthStep;

		Mosq_Float _depth;
		Mosq_Float _depthStep;
};