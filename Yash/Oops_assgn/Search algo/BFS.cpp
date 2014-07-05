#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include <queue>
#include <new>
#include <stdio.h>
using namespace cv;
using namespace std;
struct Pixel
{
    int x,y;
};

int main( int argc, char** argv )
{
    
    Mat image,grey,bin;
    int **visited,i,j,a,b,k,l,count=0,s=0,ht,wd;
    queue<Pixel> pix_queue;
   // cout << "Success" << s; s++;
    // getchar();

    image = imread("/home/yash/fuerte_workspace/sandbox/beginner_tutorials/algo/img.png", CV_LOAD_IMAGE_COLOR);  

    if(! image.data )                              
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    ht=image.rows;
    wd=image.cols;
    cvtColor(image,grey,CV_BGR2GRAY);
    imwrite("grey_img.png",grey);
    namedWindow( "Display window", WINDOW_AUTOSIZE );
    imshow( "Display window", grey );                

    waitKey(0);
    threshold(grey, bin, 100, 255, CV_THRESH_BINARY);

    imshow("Display window",bin);
    waitKey(0);
    visited=new int* [ht];
    for(i=0;i<=ht;i++)
        visited[i]=new int [wd];
    for(i=0;i<=ht;i++)
        for(j=0;j<=wd;j++)
            visited[i][j]=-1;
        ht--; wd--;
    for(i=1;i<603;i++)
        for(j=1;j<1429;j++)
        {
            if(bin.at<uchar>(i,j)==255)
            {
                if(visited[i][j]==-1)
                {
                    count++;
                    Pixel pix;
                    Pixel temp;
                    pix.x=i;
                    pix.y=j;
                    pix_queue.push(pix);
                    temp=pix_queue.front();
                    a=temp.x;
                    b=temp.y;
                    printf("a=%d,b=%d",a,b);
                    getchar();
                    while(!pix_queue.empty())
                    {
                        
                        Pixel t;
                        t=pix_queue.front();
                        a=t.x;
                        b=t.y;
                        pix_queue.pop();
                        for(k=a-1;k<=a+1;k++)
                            for(l=b-1;l<=b+1;l++)
                            {
                                if(bin.at<uchar>(k,l)==255 && visited[k][l]==-1)
                                {
                                    printf("k=%d,l%d",k,l);
                    getchar();
                                    pix.x=k;
                                    pix.y=l;
                                    pix_queue.push(pix);
                                    visited[k][l]=count;
                                }
                            }
                        visited[a][b]=count;
                    }
                    printf("got out");
                    getchar();

                }

            }
        }
       
    cout<<count;
    return 0;
}