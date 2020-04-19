#include "mosq.h"
#include "../test/test.h"

Mosq* Mosq::_mosq = nullptr;

void Mosq::init() {
		SDL_Init(SDL_INIT_VIDEO);
		window = SDL_CreateWindow(
				"Mosq SoftwareRenderer",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				WIDTH,
				HEIGHT,
				SDL_WINDOW_SHOWN
		);
		surface = SDL_GetWindowSurface(window);
		if (window == nullptr) {
				SDL_Quit();
				exit(-1);
		}
}


void Mosq::render() {
		SDL_Event event;
		bool quit = false;
		while (!quit) {
				while (SDL_PollEvent(&event)) {
						switch (event.type)
						{
						case SDL_QUIT:
								quit = true;
								break;
						case SDL_KEYDOWN:
								switch (event.key.keysym.sym) {
								case SDLK_ESCAPE:
										quit = true; break;
								}
						}
						//Test::testAll();
				}
				mainLoop();
				SDL_UpdateWindowSurface(window);
		}
}

void Mosq::mainLoop() {

}

Mosq* Mosq::getInstance() {
		if (_mosq == nullptr) {
				_mosq = new Mosq();
		}
		return _mosq;
}

void Mosq::dispose() {
		SDL_FreeSurface(surface);
		surface = nullptr;
		SDL_DestroyWindow(window);
		window = nullptr;
		SDL_Quit();
}

Mosq::Mosq() {}

Mosq::~Mosq() {}

Mosq::Mosq(const Mosq&) {}

void Mosq::operator=(const Mosq&) {}
