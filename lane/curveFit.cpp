#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <cstdlib>
#include <queue>
#include <vector>
#include <math.h>

const int threshDist=20, threshSlope=1;

float distance(int x1, int y1, int x2, int y2)
{
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

int main()
{
	cv::Mat img= cv::imread("",1);
	std::vector<Vec4i>lines;
	int maxpoints=40, minpoints=10;
	cv::HoughLinesP(img, lines,1,CV_PI/180,maxpoints,minpoints,40);
	int count=lines.size();
	visited[count];
	for(int i=0;i<count;i++)
		visited[i]=0;
	float dist[6];
	int blob=0, k=0;;

	for(int i=0;i<count;i++)
	{	
		if(visited[i]!=-1)
		visited[i]=++blob;
		k=i;
		while(k<count)
		for(int j=0;j<count;j++)
		{
			if(!visited[j])
			{
				float m1=(lines[k][3]-lines[k][1])/(lines[k][2]- lines[k][0]), m2=(lines[j][3]- lines[j][1])/(lines[j][2]- lines[j][0]);
				dist[0]=distance(lines[k][0],lines[k][1],lines[j][0], lines[j][1]);
				dist[1]=distance(lines[k][0],lines[k][1],lines[j][2], lines[j][3]);
				dist[2]=distance(lines[k][2],lines[k][3],lines[j][0], lines[j][1]);
				dist[3]=distance(lines[k][2],lines[k][3],lines[j][2], lines[j][3]);
				dist[4]=distance((lines[k][0]+lines[k][2])/2,(lines[k][1]+lines[k][3])/2,(lines[j][0]+lines[j][2])/2,(lines[j][1]+lines[j][3]/2);
				dist[5]=fabs((m1-m2)/(1+m1*m2)); // Slope comparison seems problematic
				if(dist[0]<threshDist || dist[1]<threshDist || dist[2]<threshDist || dist[3]< threshDist || dist[4]<threshDist || dist[5]<1)
				{
					visited[j]=blob;
					k=j;
				}
			}

		}


	}

	
}