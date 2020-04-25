#pragma once

#define Mosq_Float float

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
class Edge;
class Gradients;
class Cube;
class Camera;

#include "SDL.h"
#include "tool.h"
#include <iostream>
#include <memory.h>
#include "renderTarget.h"
#include "singleton.h"
#include "mosq.h"
#include "timer.h"
#include "effect.h"
#include "start.h"
#include "vertex.h"
#include "triangle.h"
#include "edge.h"
#include "gradients.h"
#include "cube.h"
#include "camera.h"

const int WIDTH = 800;
const int HEIGHT = 600;

extern SDL_Window* window;
extern SDL_Surface *surface;
extern Uint32 lastFrameTick;

