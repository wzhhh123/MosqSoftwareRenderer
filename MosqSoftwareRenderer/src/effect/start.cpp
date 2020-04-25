#include "start.h"
#include <ctime>

Start::Start(int num, Mosq_Float spread, Mosq_Float speed) : _startPos(num){
		_spread = spread;
		_speed = speed;

		for (int i = 0; i < num; ++i) {
				initStart(i);
		}
}

void Start::initStart(int index) {
		_startPos[index].x = 2 * (rand01() - 0.5f)*_spread;
		_startPos[index].y = 2 * (rand01() - 0.5f)*_spread;
		_startPos[index].z = (rand01()+1e-6)*_spread;
}


void Start::updateAndRender(std::shared_ptr<RenderTarget> rt) {
		static int a = 0;
		//if (a++ > 0) return;
		rt->clear(0, 0, 0, 0, 1);

		Mosq_Float halfWidth = WIDTH / 2.0f;
		Mosq_Float halfHeight = HEIGHT / 2.0f;


		for(int i = 0; i < _startPos.size(); ++i){
				_startPos[i].z -= Timer::deltaTimeS *_speed;
				if (_startPos[i].z < 1e-6) {
						initStart(i);
				}

				int x = (int)((_startPos[i].x / _startPos[i].z) * halfWidth + halfWidth);
				int y = (int)((_startPos[i].y / _startPos[i].z) * halfHeight + halfHeight);
				if(x < 0 || x  >= WIDTH || y < 0 || y >= HEIGHT){
						initStart(i);
				}
				else {
						rt->setPixel(x, y, 0xff, 0xff, 0xff, 0xff);
				}

		}


}
