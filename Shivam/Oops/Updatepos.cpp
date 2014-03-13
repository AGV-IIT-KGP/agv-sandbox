#include <iostream>
#include <cstdlib.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include "Oops_class.h"

float calcDist(pos a, pos b)  //Calculating only the square of the distance
{
	float dist=0;
	dist= (a.x- b.x)*(a.x- b.x) + (a.y- b.y)*(a.y- b.y);
	return dist;
}
void image::updatepos1()
{	float temp=0;
	float minDist=2*(img.rows)*(img.cols)(img.rows)*(img.cols);
	pos nearestC;
	int dice1=0;
	dice1=rand()%6 +1;
	std::cout<<"Player 1's throw is "<<dice1;
	if(dice1%2==0)
		for(int i=0;i<count;i++)
		{
			if((centroid[i]).colour==0)
			{
				temp= calcDist(currentpos1,centroid[i])
				if(temp<minDist)
				{
					minDist=temp;
					nearestC=centroid[i];
				}
			}
		}	
		
	
}