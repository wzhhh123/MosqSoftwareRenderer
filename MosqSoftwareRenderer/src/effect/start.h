

#pragma once

#include "public.h"		
#include <vector>
#include "glm.hpp"
#include "vec3.hpp"
class Start :public Effect{

private:
		Mosq_Float _spread;
		Mosq_Float _speed;
		std::vector<glm::vec3>_startPos;
		void initStart(int index);
public:
		Start(int num, Mosq_Float spread, Mosq_Float speed);
		
		void updateAndRender(std::shared_ptr<RenderTarget>);
};