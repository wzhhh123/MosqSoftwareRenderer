#include <iostream>
#include <string>
#include "mosq.h"
#include "glm/gtc/matrix_transform.hpp"
#include <algorithm>

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

		int yStart = (int) ceil(minYVert.GetY());
		int yEnd = (int)ceil(maxYVert.GetY());
		int  xStart = (int)ceil(minYVert.GetX());
		int xEnd = (int)ceil(maxYVert.GetX());

		float disX = maxYVert.GetX() - minYVert.GetX();
		float disY = maxYVert.GetY() - minYVert.GetY();

		if (disY <= 0) return;

		float xStep = disX / disY;
		float preYLength = yStart - minYVert.GetY();
		float curX = minYVert.GetX() + xStep * preYLength;

		for (int i = yStart; i < yEnd; ++i) {
				_scanBuffer[i * 2 + whichSide] = (int)ceil(curX);
				curX += xStep;
		}
}




//把scanBuffer变成了3个egde对象，扫描三角形的时候直接画，不用填充buffer再画
void Mosq::scanTriangle(Vertex  minY, Vertex midY, Vertex maxY, bool whichSide) {

		std::shared_ptr<Gradients> gradients(std::make_shared<Gradients>(minY, midY, maxY));
		std::shared_ptr<Edge>topToBottom(std::make_shared<Edge>(gradients, minY, maxY, 0));
		std::shared_ptr<Edge> topToMiddle(std::make_shared<Edge>(gradients, minY, midY, 0));
		std::shared_ptr<Edge> middleToBottom(std::make_shared<Edge>(gradients, midY, maxY, 1));

		std::shared_ptr<Edge> left = topToBottom;
		std::shared_ptr<Edge> right = topToMiddle;

		if (whichSide) {
				auto temp = left;
				left = right;
				right = temp;
		}

		int yStart = topToMiddle->getYStart();
		int yEnd = topToMiddle->getYEnd();

		for (int j = yStart; j < yEnd; ++j) {
				drawScanLine(gradients, left, right, j);
				left->step();
				right->step();
		}

		left = topToBottom;
		right = middleToBottom;

		if (whichSide) {
				auto temp = left;
				left = right;
				right = temp;
		}

		yStart = middleToBottom->getYStart();
		yEnd = middleToBottom->getYEnd();

		for (int j = yStart; j < yEnd; ++j) {
				drawScanLine(gradients, left, right, j);
				left->step();
				right->step();
		}

}

void Mosq::drawScanLine(std::shared_ptr<Gradients>gradients, std::shared_ptr<Edge> left, std::shared_ptr<Edge> right, int j) {

		int xMin = ceil(left->getX());
		int xMax = ceil(right->getX());

		float xLeftPreStep = xMin - left->getX();
		// float xRightPreStep = -(right->getX() - xMax + 1); //随便吧 就一点细微的操作

		auto minColor = left->getTexCoord() + gradients->getTexCoordXStep()* xLeftPreStep;
		auto maxColor = right->getTexCoord() + gradients->getTexCoordXStep()* xLeftPreStep;
		float lerpAmt = 0.0f;
		float lerpStep = 1 / (float)(xMax - xMin);

		for (int i = xMin; i < xMax; ++i) {
				glm::vec4 color = (1 - lerpAmt)* minColor + lerpAmt * maxColor;

				_renderTarget->setPixel(i, j, (Uint8)(color.r * 255 + 0.5f), (Uint8)(color.g * 255 + 0.5f), (Uint8)(color.b * 255 + 0.5f), (Uint8)(color.a * 255 + 0.5f));
				lerpAmt += lerpStep;
		}

}


void Mosq::scanConvertTriangle(Vertex  minY, Vertex midY, Vertex maxY, int whichSide) {

		scanConvertLine(minY, maxY, whichSide);
		scanConvertLine(minY, midY, 1-whichSide);
		scanConvertLine(midY, maxY, 1-whichSide);

}

glm::mat4 screenSpaceTransform() {
		glm::mat4 m(0.0f);

		//ndc的y是向上的，屏幕的y是向下的
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
		//右手坐标系中z向屏幕内，(x向右y向下，则z向屏幕内)，所以用右手判断顺时针是正向
		//即方向是min->max->mid顺时针时为正，这时候min->max是右边界，要填在xEnd的位置。
		int whichSide = minY.triangleAreaTimesTwo(maxY, midY) >= 0 ? 1 : 0;
		scanTriangle(minY, midY, maxY, whichSide);
		//scanConvertTriangle(minY, midY, maxY, whichSide);
		fillShape((int)ceil(minY.GetY()), (int)ceil(maxY.GetY()));
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
