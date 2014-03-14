#ifndef blobDetect_h
#define blobDetect_h
#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include "queue.h"



cv::Mat binary(cv::Mat img,float threshold)
{   cv::Mat img_gray,img_bin;
	img=cv::imread("/home/aries/Desktop/1.jpg",1);
    cvtColor(img,img_gray,CV_RGB2GRAY);
    cv::threshold(img_gray,img_bin,threshold,255.0,cv::THRESH_BINARY);	
    cv::imwrite("img_bin3.jpg",img_bin);
    return img_bin;

}

int image::bfs(image img_class)
{   
	queue q;
	int x=0,y=0;
	cv::Mat img=img_class->img_bin;
	int cols=img.cols, rows=img.rows;
    int count=1;

	for(int j=0;j<img.rows;j++)
		for(int i=0;i<img.cols;i++)
		{
           if((img.at<uchar>(i,j))==0)
           {
           		if(img_class->visited[i][j]==-1)
           		{
             		q.enqueue(i,j);
             		q.queueFront(&x,&y);
             		img_class->visited[i][j]=0;
             
             		while(!q.isEmpty())
             		{	q.queueFront(&x,&y);
             			q.dequeue();
             	        for(int l=y-1;l<=y+1;l++)
           				for(int k=x-1;k<=x+1;k++)
             			{
             				if(k>0 && k<cols && l>0 && l<rows && img_class->visited[k][l]==-1 && img.at<uchar>(i,j)==0)
             				{	
             					q.enqueue(k,l);
             					img_class->visited[k][l]=count;

             				}

             			}
             		
            		
             			img_class->visited[x][y]=count;
                    }
                    count++; 
                    std::cout<<count<<std::endl;
          		}
            

           	}
		}
	
	return count;
  	
}

#endif



