#include <iostream>
#include "public.h"
#include "glm.hpp"
using namespace std;

//这个main要带参数
int main(int argc, char *argv[]) {
		cout << "This is Mosq Software Renderer !" << endl;
		Mosq* rendererInstance = Mosq::getInstance();
		rendererInstance->init();
		Timer* timerInstance = Timer::getInstance();
		timerInstance->init();
		Camera* cameraInstance = Camera::getInstance();
		cameraInstance->init();
		rendererInstance->render();
		rendererInstance->dispose();
		return 0;
}