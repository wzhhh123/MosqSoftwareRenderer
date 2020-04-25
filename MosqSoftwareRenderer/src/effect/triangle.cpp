#include "triangle.h"
#include "glm/gtc/matrix_transform.hpp"


void Triangle::updateAndRender(std::shared_ptr<RenderTarget> rt) {

		rt->clear(0, 0, 0, 0,1);

		static Mosq_Float angle = 0;
		Mosq_Float speed = 0.001f;
		angle += Timer::deltaTimeS* speed;

		glm::mat4 indentity(1.0f);
		glm::mat4 scale = glm::scale(indentity, glm::vec3((Mosq_Float)1.3,(Mosq_Float)2.2, 0));
		glm::mat4 rotation = glm::rotate(scale, angle, glm::vec3(0, (Mosq_Float)1, 0));
		//glm::mat4 translate = glm::translate(rotation, glm::vec3(0, 0, -10));
		glm::mat4 lookat = glm::lookAt(glm::vec3(3, 3, 10), glm::vec3(0, 0, (Mosq_Float)-1), glm::vec3(0, 1, 0));
		glm::mat4 projection = glm::perspective(glm::radians(30.0f),(Mosq_Float)WIDTH/HEIGHT, 0.3f, 1000.0f);


		static SDL_Surface* image = loadBmp("../res/block.bmp");

		auto mat = projection * lookat * rotation;
		Mosq::getInstance()->fillTriangle(
				Vertex(-1, -1, 0, glm::vec4((Mosq_Float)0, (Mosq_Float)0, 0, 1)).transform(mat),
				Vertex(0, 1, 0, glm::vec4((Mosq_Float)0.5, (Mosq_Float)1.0, 0, 1)).transform(mat),
				Vertex(1, -1, 0, glm::vec4((Mosq_Float)1, (Mosq_Float)0, 1, 1)).transform(mat),
				image
				);
}
