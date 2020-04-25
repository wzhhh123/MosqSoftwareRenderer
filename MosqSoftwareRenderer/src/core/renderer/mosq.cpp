#include <iostream>
#include <string>
#include "mosq.h"
#include "glm/gtc/matrix_transform.hpp"
#include <algorithm>
#include <math.h>

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
		_renderTarget->clear(0x80, 0x80, 0x80, 1, 1);
		_startEffect.reset(new Start(4096, 1.0f, 0.001f));
		_triangleEffect.reset(new Triangle());
		_cubeEffect.reset(new Cube());
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
						Camera::getInstance()->pollEvent(event);
						//Test::testAll();
				}
				mainLoop();
				SDL_UpdateWindowSurface(window);
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

		Mosq_Float disX = maxYVert.GetX() - minYVert.GetX();
		Mosq_Float disY = maxYVert.GetY() - minYVert.GetY();

		if (disY <= 0) return;

		Mosq_Float xStep = disX / disY;
		Mosq_Float preYLength = yStart - minYVert.GetY();
		Mosq_Float curX = minYVert.GetX() + xStep * preYLength;

		for (int i = yStart; i < yEnd; ++i) {
				_scanBuffer[i * 2 + whichSide] = (int)ceil(curX);
				curX += xStep;
		}
}




//把scanBuffer变成了3个egde对象，扫描三角形的时候直接画，不用填充buffer再画
void Mosq::scanTriangle(Vertex  minY, Vertex midY, Vertex maxY, bool whichSide, SDL_Surface* image) {

 
		std::shared_ptr<Gradients> gradients(std::make_shared<Gradients>(minY, midY, maxY));
		std::shared_ptr<Edge>topToBottom(std::make_shared<Edge>(gradients, minY, maxY, 0));
		std::shared_ptr<Edge> topToMiddle(std::make_shared<Edge>(gradients, minY, midY, 0));
		std::shared_ptr<Edge> middleToBottom(std::make_shared<Edge>(gradients, midY, maxY, 1));


		//std::cout << topToBottom->getOneOverDepthStep() << " " << topToMiddle->getOneOverDepthStep() << " " << middleToBottom->getOneOverDepthStep() << std::endl;

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
				//std::cout << "draw1: " << yStart << " " << yEnd  <<" "  << left->getOneOverDepth() << " " << right->getOneOverDepth()<< std::endl;
				drawScanLine(gradients, left, right, j, image);
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

		//std::cout << yStart << " " << yEnd << std::endl;
		for (int j = yStart; j < yEnd; ++j) {
				//std::cout << "draw2: " << yStart << " " << yEnd << " " << left->getOneOverDepth() << " " << right->getOneOverDepth() << std::endl;
				drawScanLine(gradients, left, right, j, image);
				left->step();
				right->step();
		}

}


void Mosq::drawScanLine(std::shared_ptr<Gradients>gradients, std::shared_ptr<Edge> left, std::shared_ptr<Edge> right, int j, SDL_Surface* image) {

		int xMin = ceil(left->getX());
		int xMax = ceil(right->getX());

		Mosq_Float xLeftPrestep = (Mosq_Float)xMin - left->getX();

		Mosq_Float dis = (float)(right->getX() - left->getX());


		Mosq_Float curOneOverDepth = left->getOneOverDepth() + gradients->getOneOverZXStep() * xLeftPrestep;
		auto curTexCoord = left->getTexCoord() + gradients->getTexCoordXStep() * xLeftPrestep;
		Mosq_Float curDepth = left->getDepth() + gradients->getDepthXStep() *xLeftPrestep;

		Mosq_Float oneOverDepthStep = (right->getOneOverDepth() - left->getOneOverDepth()) / dis;
		auto texCoordStep = (right->getTexCoord()  - left->getTexCoord()) / dis;
		Mosq_Float depthStep = (right->getDepth() - left->getDepth()) / dis;

		for (int i = xMin; i < xMax; ++i) {

				auto texCoord = curTexCoord * (1.0f / curOneOverDepth);

				int x = texCoord.x*(image->w - 1) + 0.5f;
				int y = texCoord.y*(image->h - 1) + 0.5f;

				_renderTarget->setPixel(i, j, ((Uint32*)image->pixels)[y*image->w + x], curDepth);

				curOneOverDepth += oneOverDepthStep;
				curTexCoord += texCoordStep;
				curDepth += depthStep;

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


void Mosq::fillTriangle(Vertex v1, Vertex v2, Vertex v3, SDL_Surface* image) {

		static glm::mat4 transformToScreen = screenSpaceTransform();

		Vertex minY = v1.transform(transformToScreen).perspectiveDivide();
		Vertex midY = v2.transform(transformToScreen).perspectiveDivide();
		Vertex maxY = v3.transform(transformToScreen).perspectiveDivide();

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
		scanTriangle(minY, midY, maxY, whichSide, image);
		//scanConvertTriangle(minY, midY, maxY, whichSide);
		fillShape((int)ceil(minY.GetY()), (int)ceil(maxY.GetY()));
}

void Mosq::updateSys() {
		Timer::getInstance()->update();
		Camera::getInstance()->update();
}

void Mosq::updateWindowText() {
		std::string str =   "Mosq SoftwareRenderer FrameTime:" + std::to_string(Timer::deltaTimeS) + " Fps:" + std::to_string(Timer::fps);
		SDL_SetWindowTitle(window, str.c_str());
}

void Mosq::updateFrame() {
		//_startEffect->updateAndRender(_renderTarget);
		//_triangleEffect->updateAndRender(_renderTarget);
		_cubeEffect->updateAndRender(_renderTarget);
}

void Mosq::mainLoop() {
		updateSys();
		updateWindowText();
		updateFrame();
}


void Mosq::dispose() {
		_cubeEffect.reset();
		_triangleEffect.reset();
		_startEffect.reset();
		_renderTarget.reset(); 
		SDL_FreeSurface(surface);
		surface = nullptr;
		SDL_DestroyWindow(window);
		window = nullptr;
		SDL_Quit();
}

void clip(std::vector<Vertex>&output) {

		std::vector<Vertex>input;
		std::vector<glm::vec4> face{
		   glm::vec4(1,0,0,1),
		   glm::vec4(0,1,0,1),
		   glm::vec4(0,0,1,1),
		   glm::vec4(-1,0,0,1),
		   glm::vec4(0,-1,0,1),
		   glm::vec4(0,0,-1,1),
		};
		for (int i = 0; i < face.size(); ++i) {
				auto temp = output;
				output = input;
				input = temp;
				output.clear();
				for (int j = 0; j < input.size(); ++j) {
						auto curPoint = input[j];
						auto prePoint = input[(j - 1 + input.size()) % input.size()];
						float curDis = curPoint.GetX() * face[i].x + curPoint.GetY() * face[i].y + curPoint.GetX() * face[i].z + curPoint.GetW() * face[i].w;
						float preDis = prePoint.GetX() * face[i].x + prePoint.GetY() * face[i].y + prePoint.GetZ() * face[i].z + prePoint.GetW() * face[i].w;

						if (curDis * preDis < 0)
						{
								float t = abs(preDis) / (abs(preDis) + abs(curDis));
								auto intersetPoint = prePoint.lerp(curPoint, t);
								output.push_back(intersetPoint);
						}
						if (curDis >= 0) output.push_back(curPoint);
				}
		}
}

void Mosq::drawTriangleList(std::vector<Vertex>vertices, glm::mat4 mat, SDL_Surface* image) {


		for (int i = 0; i < vertices.size(); i ++) {
				vertices[i] = vertices[i].transform(mat);
		}

		int len = vertices.size();
		for (int i = 0; i < len; i+=3) {
				std::vector<Vertex>temp{ vertices[i], vertices[i + 1], vertices[i + 2] };
				clip(temp);
				if (temp.size() > 0) {
						vertices[i] = temp[0];
						vertices[i + 1] = temp[1];
						vertices[i + 2] = temp[2];
						for (int j = 3; j < temp.size(); ++j) {
								vertices.push_back(temp[0]);
								vertices.push_back(temp[j - 1]);
								vertices.push_back(temp[j]);
						}
				}
		}

		for (int i = 0; i < vertices.size(); i += 3) {
				Mosq::getInstance()->fillTriangle(
						vertices[i],
						vertices[i + 1],
						vertices[i + 2],
						image
				);
		}
}


Mosq::Mosq():_scanBuffer(2*HEIGHT) {}
Mosq::~Mosq() {}

//Mosq::Mosq(const Mosq&) {}
//
//void Mosq::operator=(const Mosq&) {}
