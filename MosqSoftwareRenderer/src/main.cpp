#include <iostream>
#include "public.h"
#include "mosq.h"
#include "test/test.h"
#include "glm.hpp"
using namespace std;


//���mainҪ������
int main(int argc, char *argv[]) {
		cout << "This is Mosq Software Renderer !" << endl;
		Mosq* instance = Mosq::getInstance();
		instance->init();
		instance->render();
		instance->dispose();
		return 0;
}