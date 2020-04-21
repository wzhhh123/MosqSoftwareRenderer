#pragma once

#include "public.h"

class Timer : public Singleton<Timer> {
		friend class Singleton <Timer>;
public:
		void init();
		void dispose();
		void update();
		static Uint32 deltaTime;
		static Uint32 fps;
private:
		Uint32 _lastFrame;
		Timer();
		~Timer();
};


