#include <iostream>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include "blobDetect.h"
#include "Oops_class.h"

image image;

int main()
{   pos cu
    int count=0;
	cv::Mat bin,edit;
    image.img = cv::imread("/home/aries/Desktop/1.jpg",0);
    bin=binary(image.img,190.0);
    count= bfs(image);
    image.count=count;
    findCentroid(int count) ;
    


    return 0;
}