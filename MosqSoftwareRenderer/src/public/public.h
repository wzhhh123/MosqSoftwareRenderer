#pragma once

//前向声明一下，防止头文件顺序问题
template<class T>
class Singleton;
class Mosq;
class RenderTarget;
class Timer;
class Effect;
class Start;
class Vertex;
class Triangle;

#include "tool.h"
#include <iostream>
#include <memory.h>
#include "SDL.h"
#include "renderTarget.h"
#include "singleton.h"
#include "mosq.h"
#include "timer.h"
#include "effect.h"
#include "start.h"
#include "vertex.h"
#include "triangle.h"

const int WIDTH = 800;
const int HEIGHT = 500;

extern SDL_Window* window;
extern SDL_Surface *surface;
extern Uint32 lastFrameTick;

