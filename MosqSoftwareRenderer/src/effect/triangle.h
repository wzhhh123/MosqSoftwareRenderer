#pragma once

#include "public.h"

class Triangle :public Effect {
public:
		void updateAndRender(std::shared_ptr<RenderTarget>);
};
