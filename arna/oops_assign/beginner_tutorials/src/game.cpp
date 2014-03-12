#include <iostream>
#include <cstdlib>
#include "event.h"
using namespace std;

class game: public pt{
public:
int score;
game(int a,int b): pt(a, b){
	x=a;y=b;
score=0;
};
};

