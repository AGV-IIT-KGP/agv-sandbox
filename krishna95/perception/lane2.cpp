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

struct function{
	int k;
	int fk;
};

struct polynomial{
	double a0,a1,a2,a3,a4,a5;
};


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
			{
				line(hough,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(255,0,0),3,CV_AA);color[i]='b';
			}
			else
			{
				line(hough,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(0,255,0),3,CV_AA);color[i]='g';
			}
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
				{
					line(hough,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(255,0,0),3,CV_AA);color[i]='b';
				}
			else
				{
					line(hough,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(0,255,0),3,CV_AA);color[i]='g';
				}
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
	namedWindow("hough",1);
	imshow("hough",hough);
	waitKey(0);

	Point bpt1,bpt2,gpt1,gpt2;
	bpt1.y=0;bpt2.y=1000;gpt1.y=0;gpt2.y=1000;
	for (i=0;i<lines.size();i++){
		Vec4i l=lines[i];
		if (color[i]=='b'){
			if (l[1]>bpt1.y)
				{
					bpt1.y=l[1];bpt1.x=l[0];
				}
			if (l[1]<bpt2.y){
				bpt2.y=l[1];bpt2.x=l[0];
			}
		}
		if (color[i]=='g'){
			if (l[1]>gpt1.y)
			{
				gpt1.y=l[1];gpt1.x=l[0];
			}
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
	size_t storei;
	int count=0;function pts[6];
	for (i=0;i<lines.size();i+=3){
		Vec4i l=lines[i];
		
		if (color[i]=='b' && count<6){
			pts[count].k=(l[0]+l[2])/2;
			pts[count].fk=(l[1]+l[3])/2;
			count++;
		}
	}
	cout<<count<<endl;
	cout<<pts[0].k<<" "<<pts[1].k<<" "<<pts[2].k<<" "<<pts[3].k<<" "<<pts[4].k<<" "<<pts[5].k<<endl;
	polynomial f;
	f.a0=f.a1=f.a2=f.a3=f.a4=f.a5;
	storei=(--i);
	int product=1;
	double temp0=0,temp1=0,temp2=0,temp3=0,temp4=0,temp5=0,temp6=0;
	for (int g=0;g<count;g++){
		for (int h=0;h<count;h++){
			if (h!=g){
				product*=(pts[g].k-pts[h].k);
				temp1+=pts[h].k;
				for (int n=0;n<count;n++){
					if (n!=h && n!=g){
						temp2+=pts[h].k*pts[n].k;
						for (int m=0;m<count;m++){
							if (m!=n && m!=h && m!=g){
								temp3+=pts[h].k*pts[n].k*pts[m].k;
								for  (int o=0;o<count;o++){
									if (o!=m && o!=n && o!=h && o!=g){
										temp4+=pts[h].k*pts[n].k*pts[m].k*pts[o].k;
										for (int p=0;p<count;p++){
											if (p!=o && p!=m && p!=n && p!=h && p!=g){
												temp5+=pts[h].k*pts[n].k*pts[m].k*pts[o].k*pts[p].k;
											}
										}
									}
								}
							}
						}
					}
				}

			}
		}
		f.a0+=(double)pts[g].fk/product;
		f.a1+=-(double)(temp1/product)*pts[g].fk;
		f.a2+=(double)(temp2/product/2)*pts[g].fk;
		f.a3+=-(double)(temp3/product/6)*pts[g].fk;
		f.a4+=(double)(temp4/product/24)*pts[g].fk;
		f.a5+=-(double)(temp5/product/120)*pts[g].fk;
		temp1=temp2=temp3=temp4=temp5=0;
		product=1;
	}
	cout<<f.a0<<" "<<f.a1<<" "<<f.a2<<" "<<f.a3<<" "<<f.a4<<" "<<f.a5<<" "<<endl;
	waitKey(0);
	Mat curve(lane.rows,lane.cols,CV_8UC3,cvScalarAll(0));
	int n;
	for (int m=0;m<curve.cols;m++){
		 n=(f.a0*m*m*m*m*m+f.a1*m*m*m*m+f.a2*m*m*m+f.a3*m*m+f.a4*m+f.a5);
		 cout<<"n is "<<n<<endl;
			if (n>=0 && n<curve.rows)
			{	
				cout<<"m is "<<m<<endl;
				cout<<"yes"<<endl;
				waitKey(0);
				circle(curve,Point(m,n),10,Scalar(255,255,0),-1,8,0);
			}
	}
	

	//namedWindow("hough",1);
	imshow("hough",curve);
	imwrite("hough.jpg",hough);
	waitKey(0);
}