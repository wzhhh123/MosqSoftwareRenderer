#pragma once


#include "public.h"

//三角形的一条边
class Edge {
public:
		Edge(std::shared_ptr<Gradients>gradients, Vertex start, Vertex end, int minYVertIndex);
		void step();

		int getYStart();
		int getYEnd();
		float getX();
		glm::vec4 getTexCoord();
private:
		float _curX;
		float _xStep;
		int _yStart;
		int _yEnd;
		glm::vec4 _texCoord;
		glm::vec4 _texCoordStep;
};