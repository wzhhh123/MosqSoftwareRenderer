#pragma once

#include "public.h"
#include <ctime>
#include <string>

Mosq_Float rand01();
SDL_Surface* loadBmp(std::string path);
void freeBmp(SDL_Surface * image);