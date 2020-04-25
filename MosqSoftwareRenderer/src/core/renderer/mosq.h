

#pragma once

#include "public.h"
#include <vector>
#include<memory>
#include "glm/gtc/matrix_transform.hpp"

class Mosq : public Singleton<Mosq>{
		friend class Singleton <Mosq>;
public:
		void init();
		void dispose();
		void render();
		void scanConvertTriangle(Vertex minY, Vertex midY, Vertex maxY, int whichSide);
		void scanTriangle(Vertex minY, Vertex midY, Vertex maxY, bool whichSide, SDL_Surface* image);
		void fillShape(int yMin, int yMax);
		void fillTriangle(Vertex v1, Vertex v2, Vertex v3, SDL_Surface* image);
		void drawTriangleList(std::vector<Vertex>vertices, glm::mat4 mat, SDL_Surface* image);
		
private:
		Mosq();
		~Mosq();
		//Mosq(const Mosq&);
		////½ûÖ¹¸³ÖµºÍ¿½±´
		//void operator=(const Mosq&);
		void mainLoop();

		void updateSys();
		void updateWindowText();
		void updateFrame();
		
		void drawScanLine(std::shared_ptr<Gradients>gradients, std::shared_ptr<Edge> left, std::shared_ptr<Edge> right, int j, SDL_Surface* image);
		void drawScanBuffer(int, int, int);
		void scanConvertLine(Vertex minYVert, Vertex maxYVert, int whichSide);

		std::shared_ptr<RenderTarget>_renderTarget;
		std::shared_ptr<Start>_startEffect;
		std::shared_ptr<Triangle> _triangleEffect;
		std::shared_ptr<Cube>_cubeEffect;

		std::vector<int>_scanBuffer;
		std::vector<int>_colorBuffer;
		std::vector<int>_lightingBuffer;
};