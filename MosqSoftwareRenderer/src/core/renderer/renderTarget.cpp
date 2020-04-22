

#include "renderTarget.h"

RenderTarget::RenderTarget(Uint32* pixels) {
		SDL_assert(pixels);
		this->pixels = pixels;
}

RenderTarget::~RenderTarget() {
		this->pixels = nullptr;
}

void RenderTarget::setPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	//	SDL_assert(x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT);
		bool s = x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
		if (!s) return;
		Uint32 color = SDL_MapRGBA(surface->format, r,g,b,a);
		pixels[y*WIDTH + x] = color;
}

void RenderTarget::clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
		Uint32 color = SDL_MapRGBA(surface->format, r, g, b, a);
		for (int j = 0; j < HEIGHT; ++j) {
				for (int i = 0; i < WIDTH; ++i) {
						pixels[WIDTH*j + i] = color;
				}
		}
}
