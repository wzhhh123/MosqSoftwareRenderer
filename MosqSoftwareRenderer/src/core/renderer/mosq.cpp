#include <iostream>
#include <string>
#include "mosq.h"
#include "glm/gtc/matrix_transform.hpp"

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

#include <algorithm>
void Mosq::fillShape(int yMin, int yMax) {
		yMin = std::max(0, yMin);
		yMax = std::min(yMax, HEIGHT);
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

glm::mat4 screenSpaceTransform() {
		glm::mat4 m(0.0f);

		//ndc��y�����ϵģ���Ļ��y�����µ�
		m[0][0] = WIDTH / 2; m[0][1] = 0;                   m[0][2] = 0;  m[0][3] =0 ;
		m[1][0] = 0;                m[1][1] = -HEIGHT / 2; m[1][2] = 0;  m[1][3] = 0; 
		m[2][0] = 0;                m[2][1] = 0;                   m[2][2] = 1;  m[2][3] = 0;
		m[3][0] = WIDTH / 2; m[3][1] = HEIGHT / 2;   m[3][2] = 0;  m[3][3] = 1;

		return m;
}


void Mosq::fillTriangle(Vertex v1, Vertex v2, Vertex v3) {

		static glm::mat4 transformToScreen = screenSpaceTransform();

		Vertex minY = v1.transform(transformToScreen);
		Vertex midY = v2.transform(transformToScreen);
		Vertex maxY = v3.transform(transformToScreen);


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
		//��������ϵ��z����Ļ�ڣ�(x����y���£���z����Ļ��)�������������ж�˳ʱ��������
		//��������min->max->mid˳ʱ��ʱΪ������ʱ��min->max���ұ߽磬Ҫ����xEnd��λ�á�
		int whichSide = minY.triangleAreaTimesTwo(maxY, midY) >= 0 ? 1 : 0;
		scanConvertTriangle(minY, midY, maxY, whichSide);
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
