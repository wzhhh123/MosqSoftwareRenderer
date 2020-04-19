


#include "test.h"
#include <iostream>

namespace Test {

	void writePixelTest() {

		static int i = 0;
		Uint32 color = SDL_MapRGB(surface->format, 0xff, 0, 0);
		if(i++ > 0)
			color = SDL_MapRGB(surface->format, 0xff, 0xff, 0);
		//左上方开始
		Uint32* pixel = (Uint32*)surface->pixels;

		for (int j = 0; j < HEIGHT / 2; ++j)
			for (int i = 0; i < WIDTH; ++i) {
				pixel[WIDTH*j + i] = color;
			}
	}

	void testLoadBmp() {
		SDL_Surface* image = SDL_LoadBMP("../res/mosqSoftwareRenderer.bmp");
		if (image == nullptr)
		{
			std::cout << "no such file" << std::endl;
		}
		else {
			SDL_BlitSurface(image, nullptr, surface, nullptr);
		}
		SDL_FreeSurface(image);
	}

	void testAll() {

		//pixel从左上开始
		writePixelTest();

		//如果只是直接改后缀名变成bmp的文件不能被正确读取，虽然看图软件可以正常打开，
		//但是函数貌似无法读取，返回nullptr，需要用软件另存为bmp才行
		//testLoadBmp();
	}


}