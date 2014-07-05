#include <iostream>
#include "Player.h"

using namespace std;

int main(int argc, char* argv[])
{
	Player p[2];
	gameplay game1;
	int j;
	for (j=0;j<2;j++)
	{
		p[j].x=0;
		p[j].y=0;
		p[j].score=0;
	}
	int i=game1.game(p)
	cout<<"Player"<<i<<"wins";
	cout<<"Score:"<<p[i].score;
	return 0;
}