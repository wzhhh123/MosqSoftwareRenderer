#include "gradients.h"



template<typename T>
T calcXStep(std::vector<T>val, Vertex minYVert, Vertex midYVert, Vertex maxYVert, Mosq_Float oneOverX)
{
		return
				(((val[1] - val[2]) *
				(minYVert.GetY() - maxYVert.GetY())) -
						((val[0] - val[2]) *
						(midYVert.GetY() - maxYVert.GetY()))) * oneOverX;
}

template<typename T>
T calcYStep(std::vector<T>val, Vertex minYVert, Vertex midYVert, Vertex maxYVert, Mosq_Float oneOverY)
{
		return
				(((val[1] - val[2]) *
				(minYVert.GetX() - maxYVert.GetX())) -
						((val[0] - val[2]) *
						(midYVert.GetX() - maxYVert.GetX()))) * oneOverY;
}



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

Mosq_Float Gradients::getDepth(int loc) {
		return _depth[loc];
}

Mosq_Float Gradients::getDepthXStep() {
		return _depthXStep;
}

Mosq_Float Gradients::getDepthYStep() {
		return _depthYStep;
}


Gradients::Gradients(Vertex minYVert, Vertex midYVert, Vertex maxYVert) :_texCoord(3), _oneOverZ(3), _depth(3) {

		Mosq_Float oneOverX = 1.0f /
				(((midYVert.GetX() - maxYVert.GetX()) *
				(minYVert.GetY() - maxYVert.GetY())) -
						((minYVert.GetX() - maxYVert.GetX()) *
						(midYVert.GetY() - maxYVert.GetY())));

		Mosq_Float oneOverY = -oneOverX;

	    _oneOverZ[0] = (Mosq_Float)1.0f / minYVert.GetW();
		_oneOverZ[1] = (Mosq_Float)1.0f / midYVert.GetW();
		_oneOverZ[2] = (Mosq_Float)1.0f / maxYVert.GetW();

		_depth[0] = (Mosq_Float)minYVert.GetZ();
		_depth[1] = (Mosq_Float)midYVert.GetZ();
		_depth[2] = (Mosq_Float)maxYVert.GetZ();

		//std::cout << _oneOverZ[0] << " " << _oneOverZ[1] << " " << _oneOverZ[2] << std::endl;
		
/*		_texCoord[0] = minYVert.getTexCoord();
		_texCoord[1] = midYVert.getTexCoord();
		_texCoord[2] = maxYVert.getTexCoord()*/;

		//为什么要透视校正插值，因为屏幕的点是(x/z, y/z)进行插值的，而uv对应的是(x,y)时候的uv坐标
		//为了准确插值，uv也要除以z，		
		_texCoord[0] = minYVert.getTexCoord()* _oneOverZ[0];
		_texCoord[1] = midYVert.getTexCoord()* _oneOverZ[1];
		_texCoord[2] = maxYVert.getTexCoord()* _oneOverZ[2];


		_texCoordXStep = calcXStep(_texCoord, minYVert, midYVert, maxYVert, oneOverX);
		_texCoordYStep = calcYStep(_texCoord, minYVert, midYVert, maxYVert, oneOverY);

		_oneOverZXStep = calcXStep(_oneOverZ, minYVert, midYVert, maxYVert, oneOverX);
		_oneOverZYStep = calcYStep(_oneOverZ, minYVert, midYVert, maxYVert, oneOverY);


		_depthXStep = calcXStep(_depth, minYVert, midYVert, maxYVert, oneOverX);
		_depthYStep = calcYStep(_depth, minYVert, midYVert, maxYVert, oneOverY);

}

Mosq_Float Gradients::getOneOverZ(int loc) {
		return _oneOverZ[loc];
}

Mosq_Float Gradients::getOneOverZXStep() {
		return _oneOverZXStep;
}

Mosq_Float Gradients::getOneOverZYStep() {
		return _oneOverZYStep;
}

