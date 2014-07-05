
#include "Game.h"
using namespace std;

int game(Player p[])
{
	return_data a;
	int th;
	Dice d;
	Board* bd;
	cv::Mat img=cv::imread(image.jpg);
	a = bd->board();
	int i;
	while(0)
	{
		for (i=0;i<2;i++)
		{
			th=d.dice();
			p[i].newStatus(th,return_data a);
			if(p[i].x>img->width||p[i].y>img->height)
				return i;
		}
	}
}