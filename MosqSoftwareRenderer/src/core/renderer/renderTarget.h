#pragma once

#include "public.h"
#include <vector>
class RenderTarget {
public:
		RenderTarget(Uint32* pixels);
		~RenderTarget();
		void setPixel(int x, int y, Uint8 r,Uint8 g, Uint8 b, Uint8 a);
		void setPixel(int x, int y, Uint32 color, float depth);
		void clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a, float depth);
private:
		Uint32* pixels;
		std::vector<Mosq_Float> _depthBuffer;
};