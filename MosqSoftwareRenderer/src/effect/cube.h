#pragma once

#include "public.h"

class Cube : public Effect{
public:
		void updateAndRender(std::shared_ptr<RenderTarget>);
};
