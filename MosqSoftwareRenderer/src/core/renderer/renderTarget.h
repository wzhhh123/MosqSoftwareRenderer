#pragma once

#include "public.h"

class RenderTarget {
public:
		RenderTarget(Uint32* pixels);
		~RenderTarget();
		void setPixel(int x, int y, Uint8 r,Uint8 g, Uint8 b, Uint8 a);
		void clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
private:
		Uint32* pixels;
};