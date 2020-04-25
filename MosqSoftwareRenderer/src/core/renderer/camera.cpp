

#include "camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include <algorithm>

float toRadian(float euler) {
		static float PI = acos(-1);
		return euler * PI / 180.0;
}


int lastPosX = -1;
int lastPosY = -1;
int deltaPosX = 0;
int deltaPosY = 0;

void Camera::pollEvent(SDL_Event event) {

		switch (event.type)
		{
		case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_w:
						_pos += Timer::deltaTimeMS*_front*_speed;
						break;
				case SDLK_s:
						_pos -= Timer::deltaTimeMS*_front*_speed;
						break;
				case SDLK_a:
						_pos -= Timer::deltaTimeMS*_right*_speed;
						break;
				case SDLK_d:
						_pos += Timer::deltaTimeMS*_right*_speed;
						break;
				}
				break;
		case SDL_MOUSEMOTION:
				int px = event.motion.x;
				int py = event.motion.y;
				if (lastPosX == -1) {
						lastPosX = px;
						lastPosY = py;
				}
				else {
						const float rotateSpeed = 0.1f;
						_phi += (px - lastPosX)*rotateSpeed;
						_theta += (lastPosY - py)*rotateSpeed;
						lastPosX = px;
						lastPosY = py;
				}
				break;
		}

		_theta = std::max(-89.0f, std::min(89.0f, _theta));
		Mosq_Float radianTheta = toRadian(_theta);
		Mosq_Float radanPhi = toRadian(_phi);
		_front = glm::vec3(cos(radianTheta)*cos(radanPhi), sin(radianTheta), cos(radianTheta)*sin(radanPhi));
		_right = glm::cross(_front, glm::vec3(0,1,0));
		_up = glm::cross(_right, _front);
}


void Camera::update() {
		
}


glm::mat4 Camera::getViewMatrix() {
		return glm::lookAt(_pos, _pos+_front, _up);
}

void Camera::init() {

}

void Camera::dispose() {

}


Camera::Camera():_speed(3.0f), _theta(0), _phi(-90), _front(0,0,-1), _pos(0,0,10), _up(0,1,0){
		_right = glm::cross( _front, _up);
}

Camera::~Camera(){}