#pragma once

#include "public.h"

class Camera : public Singleton<Camera>{
public:
		friend class Singleton <Camera>;
public:
		void init();
		void dispose();
		void update();
		glm::mat4 getViewMatrix();
		void pollEvent(SDL_Event);
private:
		Camera();
		~Camera();

		glm::vec3 _front;
		glm::vec3 _right;
		glm::vec3 _up;
		Mosq_Float _speed;
		Mosq_Float _theta;
		Mosq_Float _phi;
		glm::vec3 _pos;
};