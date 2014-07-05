#include "Distance.h"
using namespace std;

float dist(int x, int y, int a, int b)
{
	return sqrt((x-a)*(x-a)+(y-b)*(y-b));
}