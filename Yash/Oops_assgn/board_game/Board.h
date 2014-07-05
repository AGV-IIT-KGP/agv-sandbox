#include <ros/ros.h>
#include <stdio.h>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>     
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <math.h>
#include <cxcore.h>
#include <queue> 

using namespace std;

class Circle
{
	public:
	 	int x;
	 	int y;
	 	int color;
};

class return_data
{
	public:	
		Circle* circle;
		int cnt;
};

class Board
{
private:
	Circle* c;
public:
	int** blobDetect(int*);
	void centroid(int** ,int ,Circle* );
	Circle* board();
	int getCount();
};
