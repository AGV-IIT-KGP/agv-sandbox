#ifndef guard
#include <iostream>
#include "pos.h"

class image
    {   int score1;
        int score2;
        pos currentpos1;
        pos currentpos2;

    public:
        int count;
        cv::Mat img;
        int **visited;
        image();
        pos *centroid;
        void updatepos1;
        void updatepos2;
        void centroidUpdate();
        void findCentroid(image image);
        pos newposition();


	};

    image::image()
    {    
        score1=0,score2=0;
        currentpos1=(0,0);
        currentpos2=(0,0);
        count=0;
        score1=0;
        score2=0;
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