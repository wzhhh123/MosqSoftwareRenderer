#include "triangle.h"


void Triangle::updateAndRender(std::shared_ptr<RenderTarget> rt) {

		rt->clear(0, 0, 0, 0);
		
		Mosq::getInstance()->fillTriangle(
				Vertex(500, 100, 0),
				Vertex(430, 200, 0),
				Vertex(430, 300, 0)
				);
}
