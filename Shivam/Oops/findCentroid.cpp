#include <iostream>
#include <cstdlib.h>
#include "Oops_class.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>

void image::FindCentroid(image image)
{ 
	cv::Mat= image.img;
	int *pixels= new int[image.count);
	int blobno=0;
	rows=img.rows;
	cols=img.cols;
	for(int j=0;j<rows;j++)
	{
		for(int i=0;i<cols;i++)
		{
           if(image.visited[i][j]!=-1)
           {
            	blobno=img.at<uchar>(i,j);
            	(image.centroid[blobno]).x +=i;
            	(image.centroid[blobno]).y +=j;
            	pixels[blobno]++;
            
           }
		}
	}
	for(int i=0;i<image.count;i++)
	{
 		(image.centroid[i]).x/= pixels[i];
 		(image.centroid[i]).y/=pixels[j];
	}	
	delete pixels;            

	pos centre;
	for(int i=0;i<count;i++)
	{
		centre=centroid[i];
		cv::Vec3b point= img.at<Vec3b>(centre.x,centre.y);
		if(point[0]>200 && point[1]<100 && point[2]<100)
			(centroid[i]).colour= 0;
		else if(point[0]<100 && point[1]>200 && point[2]<100)
			(centroid[i]).colour= 1;
		else if(point[0]<100 && point[1]<100 && point[2]>200)
			(centroid[i]).colour= 2;
	}                                                                          	
}

