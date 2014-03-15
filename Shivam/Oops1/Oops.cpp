#include <iostream>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include "findCentroid.cpp"
#include "blobDetect.cpp"
#include "queue.h"

image img_class;

int main()
{   
    int flag1=1, flag2=1;
    int count=0;
	cv::Mat bin,edit;
    bin=binary(img_class.img,190.0);
    img_class.img_bin=bin;
    count= img_class.bfs();
    img_class.count=count;
    img_class.findCentroid();
    while (flag1==1 && flag2==1)
    {
    	flag1=img_class.updatepos1();
    	flag2= img_class.updatepos2();
    	img_class.printScore();
    }

    std::cout<<"GAME OVER";
    return 0;
}