#include <iostream>
#include <string>
#include "mosq.h"

void Mosq::init() {
		SDL_Init(SDL_INIT_VIDEO);
		window = SDL_CreateWindow(
				"Mosq SoftwareRenderer FrameTime:0 Fps:0",
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
		_renderTarget.reset(new RenderTarget((Uint32*)surface->pixels));
		_renderTarget->clear(0x80, 0x80, 0x80, 1);
		_startEffect.reset(new Start(4096, 1.0f, 0.001f));
		_triangleEffect.reset(new Triangle());
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
				SDL_Delay(10);
		}
}

void Mosq::drawScanBuffer(int yCoord, int xMin, int yMin) {
		_scanBuffer[yCoord * 2] = xMin;
		_scanBuffer[yCoord * 2 + 1] = yMin;
}

void Mosq::fillShape(int yMin, int yMax) {
		for (int j = yMin; j < yMax; ++j) 
		{
				int xMin = _scanBuffer[j * 2];
				int xMax = _scanBuffer[j * 2 + 1];

				for (int i = xMin; i < xMax; ++i) {
						_renderTarget->setPixel(i, j, 0xff, 0xff, 0xff, 0xff);
				}
		}
}

void Mosq::scanConvertLine(Vertex minYVert, Vertex maxYVert, int whichSide){

		int yStart = (int)minYVert.GetY();
		int yEnd = (int)maxYVert.GetY();
		int  xStart = (int)minYVert.GetX();
		int xEnd = (int)maxYVert.GetX();

		int disX = xEnd - xStart;
		int disY = yEnd - yStart;

		if (disY <= 0) return;

		float step = disX * 1.0f / disY;
		float curX = xStart;

		for (int i = yStart; i < yEnd; ++i) {
				_scanBuffer[i * 2 + whichSide] = (curX + step);
				curX += step;
		}
}


void Mosq::scanConvertTriangle(Vertex  minY, Vertex midY, Vertex maxY, int whichSide) {


		scanConvertLine(minY, maxY, whichSide);
		scanConvertLine(minY, midY, 1-whichSide);
		scanConvertLine(midY, maxY, 1-whichSide);

}

void Mosq::fillTriangle(Vertex v1, Vertex v2, Vertex v3) {

		Vertex minY = v1;
		Vertex midY = v2;
		Vertex maxY = v3;

		if (minY.GetY() > midY.GetY()) {
				auto temp = minY;
				minY = midY;
				midY = temp;
		}

		if (minY.GetY() > maxY.GetY()) {
				auto temp = minY;
				minY = maxY;
				maxY = temp;
		}

		if (midY.GetY() > maxY.GetY()) {
				auto temp = midY;
				midY = maxY;
				maxY = temp;
		}

		//int whichSide = maxY.GetX() >= midY.GetX();
		//右手坐标系中z向屏幕内，(x向右y向下，则z向屏幕内)，所以用右手判断顺时针是正向
		//即方向是min->max->mid顺时针时为正，这时候min->max是右边界，要填在xEnd的位置。
		int whichSide = minY.triangleArea(maxY, midY) >= 0 ? 1 : 0;
		scanConvertTriangle(minY, midY, maxY, 1);
		fillShape((int)minY.GetY(), (int)maxY.GetY());
}

void Mosq::updateSys() {
		Timer::getInstance()->update();
}

void Mosq::updateWindowText() {
		std::string str =   "Mosq SoftwareRenderer FrameTime:" + std::to_string(Timer::deltaTime) + " Fps:" + std::to_string(Timer::fps);
		SDL_SetWindowTitle(window, str.c_str());
}

void Mosq::updateFrame() {
		//_startEffect->updateAndRender(_renderTarget);
		_triangleEffect->updateAndRender(_renderTarget);
}

void Mosq::mainLoop() {
		updateSys();
		updateWindowText();
		updateFrame();
}


void Mosq::dispose() {
		_triangleEffect.reset();
		_startEffect.reset();
		_renderTarget.reset(); 
		SDL_FreeSurface(surface);
		surface = nullptr;
		SDL_DestroyWindow(window);
		window = nullptr;
		SDL_Quit();
}

Mosq::Mosq():_scanBuffer(2*HEIGHT) {}
Mosq::~Mosq() {}

//Mosq::Mosq(const Mosq&) {}
//
//void Mosq::operator=(const Mosq&) {}
