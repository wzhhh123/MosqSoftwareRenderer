

#include "edge.h"

Edge::Edge(std::shared_ptr<Gradients>  gradients, Vertex minYVert, Vertex maxYVert, int minYVertIndex) {

		_yStart = (int)ceil(minYVert.GetY());
		_yEnd = (int)ceil(maxYVert.GetY());

		float disX = maxYVert.GetX() - minYVert.GetX();
		float disY = maxYVert.GetY() - minYVert.GetY();

		float preYLength = _yStart - minYVert.GetY();
		_xStep = disX / disY;
		_curX = minYVert.GetX() + _xStep * preYLength;

		float preXLength = _curX - minYVert.GetX();

		_texCoord = gradients->getTexCoord(minYVertIndex) +
				preXLength * gradients->getTexCoordXStep() +
				preYLength * gradients->getTexCoordYStep();

		_texCoordStep = gradients->getTexCoordYStep() + gradients->getTexCoordXStep()*_xStep;
}

float Edge::getX() {
		return _curX;
}

glm::vec4 Edge::getTexCoord() {
		return _texCoord;
}

void Edge::step() {
		_curX += _xStep;
		_texCoord += _texCoordStep;
}

int Edge::getYStart() {
		return _yStart;
}
int Edge::getYEnd() {
		return _yEnd;
}

/*

void Mosq::scanConvertLine(Vertex minYVert, Vertex maxYVert, int whichSide) {

		int yStart = (int)ceil(minYVert.GetY());
		int yEnd = (int)ceil(maxYVert.GetY());
		int  xStart = (int)ceil(minYVert.GetX());
		int xEnd = (int)ceil(maxYVert.GetX());

		float disX = maxYVert.GetX() - minYVert.GetX();
		float disY = maxYVert.GetY() - minYVert.GetY();

		if (disY <= 0) return;

		float xStep = disX / disY;
		float preYLength = yStart - minYVert.GetY();
		float curX = minYVert.GetX() + xStep * preYLength;

		for (int i = yStart; i < yEnd; ++i) {
				_scanBuffer[i * 2 + whichSide] = (int)ceil(curX);
				curX += xStep;
		}
}

*/