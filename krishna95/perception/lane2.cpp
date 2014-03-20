 #include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/operations.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <math.h>
using namespace cv;
using namespace std;

double dist(int x1,int x2,int y1,int y2){
	return sqrt((double)(x1-x2)*(x1-x2)+(double)(y1-y2)*(y1-y2));
}

double angle(int x1,int x2,int y1,int y2){
	return atan((double)(y1-y2)/(x1-x2));
}

double minimum(double dis1,double dis2,double dis3,double dis4){
	if (dis1<=dis2 && dis1<=dis3 && dis1<=dis4)
		return dis1;
	if (dis2<=dis1 && dis2<=dis3 && dis2<=dis4)
		return dis2;
	if (dis3<=dis1 && dis3<=dis2 && dis3<=dis4)
		return dis3;
	else
		return dis4;
}


 int main(){
	const int x=200;
	int mid_y=0,mid_x=0;
	double dis=0,average=0,theta,av_theta=0,dis1,dis2;
	vector<Vec4i> lines;
	Mat lane=imread("lane.png",1);
	namedWindow("source",CV_WINDOW_AUTOSIZE);
	imshow("source",lane);
	waitKey(0);
	cvtColor(lane,lane,CV_BGR2GRAY);
	Mat hough(lane.rows,lane.cols,CV_8UC3,cvScalarAll(0));
	HoughLinesP(lane,lines,1,CV_PI/180,10,5,50);
	size_t i,min_ix=10000,max_ix=0,min_iy=1000,max_iy=0;
	for ( i=0;i<lines.size();i++)
	{
		Vec4i l=lines[i];
		mid_x=(l[0]+l[2])/2;
		mid_y=(l[1]+l[3])/2;
		dis=dist(mid_x,0,mid_y,0);
		average+=dis;
		theta=angle(l[0],l[2],l[1],l[3]);
		av_theta+=theta;
		line(hough,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(255,255,255),3,CV_AA);
	}
	average/=(--i);
	av_theta/=i;
	char color[lines.size()];
	cout<<average<<" "<<av_theta<<endl;
	if (av_theta<-0.5){
		for ( i=0;i<lines.size();i++)
		{
			Vec4i l=lines[i];
			mid_x=(l[0]+l[2])/2;
			mid_y=(l[1]+l[3])/2;
			dis=dist(mid_x,0,mid_y,0);
			if (dis<average)
				{line(hough,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(255,0,0),3,CV_AA);color[i]='b';}
			else
				{line(hough,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(0,255,0),3,CV_AA);color[i]='g';}
		}
	}
	if (av_theta>0.5){
		for ( i=0;i<lines.size();i++)
		{
			Vec4i l=lines[i];
			mid_x=(l[0]+l[2])/2;
			mid_y=(l[1]+l[3])/2;
			dis=dist(mid_x,0,mid_y,lane.rows-1);
			if (dis<average)
				{line(hough,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(255,0,0),3,CV_AA);color[i]='b';}
			else
				{line(hough,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(0,255,0),3,CV_AA);color[i]='g';}
		}
	}
	if (av_theta<0.5 && av_theta>-0.5){
		for ( i=0;i<lines.size();i++)
		{
			Vec4i l=lines[i];
			theta=angle(l[0],l[2],l[1],l[3]);
			if (theta<0)
				{line(hough,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(255,0,0),3,CV_AA);color[i]='b';}
			else
				{line(hough,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(0,255,0),3,CV_AA);color[i]='g';}
		}
	}
	Point bpt1,bpt2,gpt1,gpt2;
	bpt1.y=0;bpt2.y=1000;gpt1.y=0;gpt2.y=1000;
	for (i=0;i<lines.size();i++){
		Vec4i l=lines[i];
		if (color[i]=='b'){
			if (l[1]>bpt1.y)
				{bpt1.y=l[1];bpt1.x=l[0];}
			if (l[1]<bpt2.y){
				bpt2.y=l[1];bpt2.x=l[0];
			}
		}
		if (color[i]=='g'){
			if (l[1]>gpt1.y)
				{gpt1.y=l[1];gpt1.x=l[0];}
			if (l[1]<gpt2.y){
				gpt2.y=l[1];gpt2.x=l[0];
			}
		}

	}
	cout<<bpt1.x<<" "<<bpt1.y<<endl;
	dis1=dist(bpt1.x,gpt1.x,bpt1.y,gpt1.y);
	dis2=dist(bpt2.x,gpt2.x,bpt2.y,gpt2.y);
	if (dis1<x || dis2<x)
		cout<<"both lines are same "<<endl;
	else
		cout<<"both lines are distinct"<<endl;

	namedWindow("hough",1);
	imshow("hough",hough);
	imwrite("hough.jpg",hough);
	waitKey(0);
}