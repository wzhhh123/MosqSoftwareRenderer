#pragma once

#include "public.h"

class Timer : public Singleton<Timer> {
		friend class Singleton <Timer>;
public:
		void init();
		void dispose();
		void update();
		static Uint32 deltaTimeS;
		static Uint32 fps;
		static float deltaTimeMS;

private:
		Uint32 _lastFrame;
		Timer();
		~Timer();
};


