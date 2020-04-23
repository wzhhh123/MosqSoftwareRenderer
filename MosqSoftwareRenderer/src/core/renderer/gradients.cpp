#include "gradients.h"

glm::vec4 Gradients::getTexCoord(int loc)
{
		return _texCoord[loc];
}

glm::vec4 Gradients::getTexCoordXStep() {
		return _texCoordXStep;
}


glm::vec4 Gradients::getTexCoordYStep() {
		return _texCoordYStep;
}

Gradients::Gradients(Vertex minYVert, Vertex midYVert, Vertex maxYVert):_texCoord(3) {

		float oneOverX = 1.0f /
				(
				(midYVert.GetX() - maxYVert.GetX())*
				(minYVert.GetY() - maxYVert.GetY()) +
						(maxYVert.GetX() - minYVert.GetX())*
						(midYVert.GetY() - maxYVert.GetY())
						);

		float oneOverY = -oneOverX;

		_texCoord[0] = minYVert.getTexCoord();
		_texCoord[1] = midYVert.getTexCoord();
		_texCoord[2] = maxYVert.getTexCoord();


		_texCoordXStep = oneOverX * (
						(_texCoord[1] - _texCoord[2])*(minYVert.GetY() - maxYVert.GetY()) +
						(_texCoord[2] - _texCoord[0])*(midYVert.GetY() - maxYVert.GetY())
				);

		_texCoordYStep = oneOverY * (
				(_texCoord[1] - _texCoord[2])*(minYVert.GetX() - maxYVert.GetX()) +
				(_texCoord[2] - _texCoord[0])*(midYVert.GetX() - maxYVert.GetX())
				);

}
