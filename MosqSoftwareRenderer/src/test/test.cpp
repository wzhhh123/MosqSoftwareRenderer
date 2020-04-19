


#include "test.h"
#include <iostream>

namespace Test {

	void writePixelTest() {

		static int i = 0;
		Uint32 color = SDL_MapRGB(surface->format, 0xff, 0, 0);
		if(i++ > 0)
			color = SDL_MapRGB(surface->format, 0xff, 0xff, 0);
		//���Ϸ���ʼ
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

		//pixel�����Ͽ�ʼ
		writePixelTest();

		//���ֻ��ֱ�Ӹĺ�׺�����bmp���ļ����ܱ���ȷ��ȡ����Ȼ��ͼ������������򿪣�
		//���Ǻ���ò���޷���ȡ������nullptr����Ҫ��������Ϊbmp����
		//testLoadBmp();
	}


}