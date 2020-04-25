#include "cube.h"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

std::vector<Vertex> getCubeVertexList() {

		std::vector<Vertex>res;

		std::vector<Mosq_Float> vertices {
		 0.5, -0.5, 0.5 , 0.0, 0.0 , 0.5, 0.5, 0.5 , 0.0, 1.0 , -0.5, 0.5, 0.5 , 1.0, 1.0 , 0.5, -0.5, 0.5 , 0.0, 0.0 , -0.5, 0.5, 0.5 , 1.0, 1.0 , -0.5, -0.5, 0.5 , 1.0, 0.0 , 0.5, 0.5, 0.5 , 0.0, 0.0 , 0.5, 0.5, -0.5 , 0.0, 1.0 , -0.5, 0.5, -0.5 , 1.0, 1.0 , 0.5, 0.5, 0.5 , 0.0, 0.0 , -0.5, 0.5, -0.5 , 1.0, 1.0 , -0.5, 0.5, 0.5 , 1.0, 0.0 , 0.5, 0.5, -0.5 , 0.0, 0.0 , 0.5, -0.5, -0.5 , 0.0, 1.0 , -0.5, -0.5, -0.5 , 1.0, 1.0 , 0.5, 0.5, -0.5 , 0.0, 0.0 , -0.5, -0.5, -0.5 , 1.0, 1.0 , -0.5, 0.5, -0.5 , 1.0, 0.0 , 0.5, -0.5, -0.5 , 0.0, 0.0 , 0.5, -0.5, 0.5 , 0.0, 1.0 , -0.5, -0.5, 0.5 , 1.0, 1.0 , 0.5, -0.5, -0.5 , 0.0, 0.0 , -0.5, -0.5, 0.5 , 1.0, 1.0 , -0.5, -0.5, -0.5 , 1.0, 0.0 , -0.5, -0.5, 0.5 , 0.0, 0.0 , -0.5, 0.5, 0.5 , 0.0, 1.0 , -0.5, 0.5, -0.5 , 1.0, 1.0 , -0.5, -0.5, 0.5 , 0.0, 0.0 , -0.5, 0.5, -0.5 , 1.0, 1.0 , -0.5, -0.5, -0.5 , 1.0, 0.0 , 0.5, -0.5, -0.5 , 0.0, 0.0 , 0.5, 0.5, -0.5 , 0.0, 1.0 , 0.5, 0.5, 0.5 , 1.0, 1.0 , 0.5, -0.5, -0.5 , 0.0, 0.0 , 0.5, 0.5, 0.5 , 1.0, 1.0 , 0.5, -0.5, 0.5 , 1.0, 0.0
		};

		for (int i = 0; i < vertices.size(); i += 5)
		{
				Vertex t(vertices[i], vertices[i + 1], vertices[i + 2], glm::vec4(vertices[i + 3], vertices[i + 4], 0.0f, 0.0f));
				res.push_back(t);
		}

		return res;
}

void Cube::updateAndRender(std::shared_ptr<RenderTarget> rt) {

		rt->clear(0, 0, 0, 0, 1);

		static Mosq_Float angle = 0;
		Mosq_Float speed = 0.001f;
		angle += Timer::deltaTimeS* speed;

		glm::mat4 indentity(1.0f);
		glm::mat4 scale = glm::scale(indentity, glm::vec3((Mosq_Float)1.0, (Mosq_Float)1.0, (Mosq_Float)1.0));
		glm::mat4 rotation = glm::rotate(scale, angle, glm::vec3((Mosq_Float)0, (Mosq_Float)1, (Mosq_Float)0));
		//glm::mat4 lookat = glm::lookAt(glm::vec3(3, 3, 10), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
		glm::mat4 lookat = Camera::getInstance()->getViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(30.0f), (Mosq_Float)WIDTH / HEIGHT, 5.0f, 15.0f);


		static SDL_Surface* image = loadBmp("../res/awesomeface.bmp");
		static std::vector<Vertex> vertices = getCubeVertexList();
		//auto mat = projection * lookat * rotation;
		auto mat = projection * lookat;


		Mosq::getInstance()->drawTriangleList(vertices, mat, image);

	
}
