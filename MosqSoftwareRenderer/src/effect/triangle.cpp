#include "triangle.h"
#include "glm/gtc/matrix_transform.hpp"


void Triangle::updateAndRender(std::shared_ptr<RenderTarget> rt) {

		rt->clear(0, 0, 0, 0);

		static float angle = 0;
		float speed = 0.01f;
		angle += Timer::deltaTime* speed;

		glm::mat4 indentity(1.0f);
		glm::mat4 scale = glm::scale(indentity, glm::vec3(1.3f,2.2f, 0));
		glm::mat4 rotation = glm::rotate(scale, angle, glm::vec3(0, 1, 0));
		//glm::mat4 translate = glm::translate(rotation, glm::vec3(0, 0, -10));
		glm::mat4 lookat = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
		glm::mat4 projection = glm::perspective(glm::radians(30.0f),(float)WIDTH/HEIGHT, 0.3f, 1000.0f);


		auto mat = projection * lookat * rotation;
		Mosq::getInstance()->fillTriangle(
				Vertex(0, 1, 0).transform(mat).perspectiveDivide(),
				Vertex(1, 0, 0).transform(mat).perspectiveDivide(),
				Vertex(0, 0, 0).transform(mat).perspectiveDivide()
				);
}
