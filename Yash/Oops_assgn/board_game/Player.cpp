#include "Player.h"
using namespace std;

void Player::updtPos(int color, Circle* circle,int count )
{
	Distance d;
	int i,j;
	float min=d.dist(0,0,1024,768);
	for(i=0;i<bd->getCount();i++)
	{
		if(p.x<circle[i].x && p.y<circle[i].y)
			if(min>d.dist(x,y,circle[i].x,circle[i].y))
			{
				j=i;
				min=d.dist(x,y,circle[i].x,circle[i].y);
			}
	}
	p.x=circle[i].x;
	p.y=circle[i].y;
}


void Player::newStatus(int th, return_data a)
{
	if(th%2==0)
	{
		p.updtPos(1,a.circle, a.cnt);
		p.score+=2*th;
		return;
	}
	if(th==1)
	{
		p.updtPos(2,a.circle, a.cnt);
		score+=10;
		return;
	}
	else 
	{
		p.updtPos(3,a.circle,a.cnt);
		p.score+=th;
		return;
	}
}


