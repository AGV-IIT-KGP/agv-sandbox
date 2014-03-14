#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <cstdlib>
#include "Oops_class.h"

//Has definitions of functions findCentroid, calcDist, Updatepos1, Updatepos2, printScore
void image::findCentroid(cv::Mat img)
{ 
	
	int *pixels= new int[count];
	int blobno=0;
	int rows=img.rows;
	int cols=img.cols;
	for(int j=0;j<rows;j++)
	{
		for(int i=0;i<cols;i++)
		{
           if(visited[i][j]!=-1)
           {
            	blobno=img.at<uchar>(i,j);
            	(centroid[blobno]).x +=i;
            	(centroid[blobno]).y +=j;
            	pixels[blobno]++;
            
           }
		}
	}
	for(int i=0;i<count;i++)
	{
 		(centroid[i]).x/= pixels[i];
 		(centroid[i]).y/=pixels[i];
	}	
	delete pixels;            

	pos centre;
	for(int i=0;i<count;i++)
	{
		centre=centroid[i];
		cv::Vec3b point= img.at<cv::Vec3b>(centre.x,centre.y);
		if(point[0]>200 && point[1]<100 && point[2]<100)
			(centroid[i]).colour= 0;
		else if(point[0]<100 && point[1]>200 && point[2]<100)
			(centroid[i]).colour= 1;
		else if(point[0]<100 && point[1]<100 && point[2]>200)
			(centroid[i]).colour= 2;
	}                                                                          	
}


float calcDist(pos a, pos b)  //Calculating only the square of the distance
{
	float dist=0;
	dist= (a.x- b.x)*(a.x- b.x) + (a.y- b.y)*(a.y- b.y);
	return dist;
}
int image::updatepos1()
{	
	float temp=0;
	float minDist=2*(img.rows)*(img.cols)*(img.rows)*(img.cols);
	pos nearestC;
	int dice1=0;
	dice1=rand()%6 +1;
	std::cout<<"Player 1's throw is "<<dice1;
	if(dice1%2==0)
		for(int i=0;i<count;i++)
		{
			if((centroid[i]).colour==0)
			{
				temp= calcDist(currentpos1,centroid[i]);
				if(temp<minDist)
				{
					minDist=temp;
					nearestC=centroid[i];
				}
				currentpos1=nearestC;
				score1+= 2*dice1;
			}
		}
	else if(dice1==1)
	{
		for(int i=0;i<count;i++)
		{
			if((centroid[i]).colour==2)
			{
				temp=calcDist(currentpos1,centroid[i]);
				if(temp<minDist)
				{
					minDist=temp;
					nearestC=centroid[i];
				}
				currentpos1=nearestC;
				score1+=10;
			}
		}
	}

	else 
	{
		for(int i=0;i<count;i++)
		{
			if((centroid[i]).colour==1)
			{
				temp=calcDist(currentpos1,centroid[i]);
				if(temp<minDist)
				{
					minDist=temp;
					nearestC=centroid[i];
				}
				currentpos1=nearestC;
				score1+=dice1;;
			}
		}
	}
	

	if(currentpos1.x==nearestC.x && currentpos1.y==nearestC.y)
		return 0;
	std::cout<<"New position of player 1 is "<<"("<<currentpos1.x<<","<<currentpos1.y<<")";		
	return 1;

}

int image::updatepos2()
{
	float temp=0;
	float minDist=2*(img.rows)*(img.cols)*(img.rows)*(img.cols);
	pos nearestC;
	int dice2=0;
	dice2=rand()%6 +1;
	std::cout<<"Player 2's throw is "<<dice2;
	if(dice2%2==0)
		for(int i=0;i<count;i++)
		{
			if((centroid[i]).colour==0)
			{
				temp= calcDist(currentpos2,centroid[i]);
				if(temp<minDist)
				{
					minDist=temp;
					nearestC=centroid[i];
				}
			}
			currentpos2=nearestC;
			score2 += 2*dice2;
		}
	else if(dice2==1)
	{
		for(int i=0;i<count;i++)
		{
			if((centroid[i]).colour==2)
			{
				temp=calcDist(currentpos2,centroid[i]);
				if(temp<minDist)
				{
					minDist=temp;
					nearestC=centroid[i];
				}
				currentpos2=nearestC;
				score2+=10;
			}
		}
	}

	else 
	{
		for(int i=0;i<count;i++)
		{
			if((centroid[i]).colour==1)
			{
				temp=calcDist(currentpos2,centroid[i]);
				if(temp<minDist)
				{
					minDist=temp;
					nearestC=centroid[i];
				}
				currentpos2=nearestC;
				score2+=dice2;;
			}
		}
	}
	

	if(currentpos2.x==nearestC.x && currentpos2.y==nearestC.y)
		return 0;
	std::cout<<"New position of player 2 is "<<"("<<currentpos2.x<<","<<currentpos2.y<<")";
	return 1;
}

void image::printScore()
{
	std::cout<<"Player 1's score= "<<score1<<std::endl;
	std::cout<<"Player 2's score= "<<score2<<std::endl;
}

