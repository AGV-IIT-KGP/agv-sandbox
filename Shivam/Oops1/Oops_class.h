#ifndef Oops_class_h
#define Oops_class_h

#include <iostream>
#include <opencv/highgui.h>
#include <opencv/cv.h>

class pos
    {
     public:
        pos()
        {
            x=0,y=0;colour=0;
        }
        int x;
        int y;
        int colour;
    };

class image
    {   int score1;
        int score2;
        pos currentpos1;
        pos currentpos2;

    public:
        int count;
        cv::Mat img;
        cv::Mat img_bin;
        int **visited;
        image();
        pos *centroid;
        int bfs();
        int updatepos1();
        int updatepos2();
        void findCentroid();
       void printScore();
    };

    image::image()
    {    
        score1=0,score2=0;
        count=0;
        score1=0;
        score2=0;
        img = cv::imread("/home/aries/Desktop/1.jpg",0);
        int rows=img.rows;
        int cols=img.cols;
        visited= new int*[rows];
        for(int j=0;j<rows;j++)
        {   visited[j]= new int[cols];
        for(int i=0;i<cols;i++)
          visited[i][j]=-1;
        }
        centroid= new pos[count];

    }   

#endif