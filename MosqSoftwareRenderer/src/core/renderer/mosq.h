

#pragma once

#include "public.h"

class Mosq {
public:
		static Mosq* getInstance();
		void init();
		void dispose();
		void render();
private:
		Mosq();
		~Mosq();
		Mosq(const Mosq&);
		//½ûÖ¹¸³ÖµºÍ¿½±´
		void operator=(const Mosq&);
		void mainLoop();
		static Mosq* _mosq;
};