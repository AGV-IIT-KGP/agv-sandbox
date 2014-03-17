#include "Board.h"
using namespace std;



int** blobDetect(int *count)
{	
	int i,j,k,l,x,y,d;
	queue<int > myqueue1;
	queue<int > myqueue2;
	cv::Mat img=imread(image.jpg);
	int ht=img->cols;
 	int wd=img->rows;
	Mat gray;
 	cvtCor( image, gray, CV_BGR2GRAY );
 	imwrite( "Gray_Image.jpg", gray);
 	cv::Scalar intensity;
 	

 	int **visited;
	visited = (int**)malloc(768*sizeof(int*)); 
 	for(i=0;i<ht;i++)
		visited[i]=(int*)malloc((1024*sizeof(int));
 	

 	for(i=0;i<img->cols;i++)
 		for(j=0;j<img->rows;j++)
 			{
 				intensity= grey.at<uchar>(i, j);
 				if (intensity>127)
 					grey.at<uchar>(i, j)=255;
 				else
 					grey.at<uchar>(i, j)=0;
 			}


 	
 	
 	
 	for(i=0;i<ht;i++)
		for(j=0;j<wd;j++)
			visited[i][j]=-1;



	for(i=1;i<ht-1;i++)
		for(j=1;j<wd-1;j++)
		{
			if(grey.at<uchar>(i, j)==0)
			{
				if(visited[i][j]==-1)
				{
					*count=*count+1;
					
						myqueue1.front=NULL;
						myqueue1.push(i);
						myqueue1.front(&x);
						myqueue2.front=NULL;
						myqueue2.push(j);
						myqueue2.front(&y);
					
					
				}
				while(!isEmpty())
				{
					myqueue1.front(&x);
					myqueue1.pop();
					myqueue2.front(&y);
					myqueue2.pop();
					for(k=x-1;k<=x+1;k++)
						for(l=y-1;l<=y+1;l++)
						{
							intensity=grey.at<uchar>(i, j);
							if(intensity==0 && visited[k][l]==-1)
							{
								myqueue1.push(k);
								myqueue2.push(l);
								visited[k][l]=*count;
							}
						}
						visited[x][y]=*count;
				}
			}
		}
		
	return visited;
}

void centroid(int** output,int count,Circle* c)
{
	int i,j;
	double count_pixel[count+1];
 	cv::Mat img=cv::imread(image.jpg);
	for(i=0;i<img.rows;i++)
		{
			for(j=0;j<img.rows;j++)
			{
				int value;
				value=output[i][j];
				if(value!=-1)
				{
					c[value].x+=j;
					c[value].y+=i;
					count_pixel[value]++;
				}
			}
		}
	for(i=1;i<count+1;i++)
	{
		c[i].x/=count_pixel[i];
		c[i].y/=count_pixel[i];
	}
	cv::Scalar intensity;
	for(i=1;i<count+1;i++)
	{
		cv::Vec3b intensity = img.at<Vec3b>(&c[i].y, &c[i].x);
		if(intensity.val[0]>200) c[i].color=1;
		else if (intensity.val[1]>200) c[i].color=2;
		else (intensity.val[2]>200) c[i].color=3;	
	}
}
return_data board()
{	
	return_data a;
	int **output=NULL;
	int count;
	output=blobDetect(&count);
	Circle c[100];
	centroid(output,count,c);
	a.circle=c;
	a.cnt=count;
	return a;
}


