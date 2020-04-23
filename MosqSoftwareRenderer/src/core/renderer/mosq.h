

#pragma once

#include "public.h"
#include <vector>
#include<memory>

class Mosq : public Singleton<Mosq>{
		friend class Singleton <Mosq>;
public:
		void init();
		void dispose();
		void render();
		void scanConvertTriangle(Vertex minY, Vertex midY, Vertex maxY, int whichSide);
		void scanTriangle(Vertex minY, Vertex midY, Vertex maxY, bool whichSide);
		void fillShape(int yMin, int yMax);
		void fillTriangle(Vertex v1, Vertex v2, Vertex v3);
		
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
		
		void drawScanLine(std::shared_ptr<Gradients>gradients, std::shared_ptr<Edge> left, std::shared_ptr<Edge> right, int j);
		void drawScanBuffer(int, int, int);
		void scanConvertLine(Vertex minYVert, Vertex maxYVert, int whichSide);

		std::shared_ptr<RenderTarget>_renderTarget;
		std::shared_ptr<Start>_startEffect;
		std::shared_ptr<Triangle> _triangleEffect;

		std::vector<int>_scanBuffer;
		std::vector<int>_colorBuffer;
		std::vector<int>_lightingBuffer;
};