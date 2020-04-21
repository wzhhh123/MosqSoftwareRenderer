

#pragma once

#include "public.h"		
#include <vector>
#include "glm.hpp"
#include "vec3.hpp"
class Start :public Effect{

private:
		float _spread;
		float _speed;
		std::vector<glm::vec3>_startPos;
		void initStart(int index);
public:
		Start(int num, float spread, float speed);
		
		void updateAndRender(std::shared_ptr<RenderTarget>);
};