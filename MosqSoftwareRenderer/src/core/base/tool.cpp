#include <tool.h>


float rand01()
{
		static bool once = false;
		if (!once) srand(time(NULL)), once = true;
		return (rand() % RAND_MAX) / (RAND_MAX*1.0f);
}