#include <iostream>
#include <cstdlib>
#include "event.h"
using namespace std;

class game: public pt{
public:
int winner_score,winner_id;
game(int a,int b): pt(a, b){
	x=a;y=b;
winner_score=0;winner_id=0;
};
};

