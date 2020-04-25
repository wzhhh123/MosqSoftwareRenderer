#include <tool.h>


Mosq_Float rand01()
{
		static bool once = false;
		if (!once) srand(time(NULL)), once = true;
		return (rand() % RAND_MAX) / (RAND_MAX*1.0f);
}


void freeBmp(SDL_Surface * image) {
		SDL_FreeSurface(image);
}


SDL_Surface* loadBmp(std::string path)
{
		// "../res/mosqSoftwareRenderer.bmp"
		SDL_Surface* image = SDL_LoadBMP(path.c_str());
		if (image == nullptr)
		{
				std::cout << "no such file" << std::endl;
		}
		/*else {
				SDL_BlitSurface(image, nullptr, surface, nullptr);
		}
		SDL_FreeSurface(image);*/
		return image;
}