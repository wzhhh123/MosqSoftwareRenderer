

#include "timer.h"

Uint32 Timer::deltaTimeS = 0;
Uint32 Timer::fps = 0;

float Timer::deltaTimeMS = 0;

void Timer::init() {
		_lastFrame = 0;
}

void Timer::update() {
		static Uint32 frameCnt = 0;
		static Uint32 tickCnt = 0;

		Uint32 temp = SDL_GetTicks();
		deltaTimeS = temp - _lastFrame;
		deltaTimeMS = deltaTimeS / 1000.0f;
		_lastFrame = temp;

		frameCnt++;
		tickCnt += deltaTimeS;
		if (tickCnt >= 1000) {
				fps = frameCnt;
				frameCnt = 0;
				tickCnt -= 1000;
		}
}


void Timer::dispose() {
		_lastFrame = 0;
}


Timer::Timer() {
}


Timer::~Timer() {
}