#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

cv::Mat inputimg()
{
	cv::Mat img;
	img=cv::imread("./images.jpeg",1);
	return img;
}

void showimg(cv::Mat img)
{
	cv::imshow("window",img);
	cv::waitKey(500);
	cv::destroyAllWindows();
}

cv::Mat cvtbinary(cv::Mat img,char color)
{
	int i,j;
	cv::Mat binary(img.rows,img.cols,CV_8UC1,cvScalarAll(0));
	for(i=0;i<img.rows;++i){
		for(j=0;j<img.cols;++j){
			if(img.at<cv::Vec3b>(i,j)[color]>=200)
				binary.at<uchar>(i,j)=255;
		}
	}
	return binary;
}

char if_circle(cv::Mat img,int *x,int *y,char color)
{
	img=cvtbinary(img,color);
	cv::Rect ROI(*x,*y,img.cols-*x,img.rows-*y);
	img=img(ROI);
	showimg(img);
	std::vector<cv::Vec3f> circles;
	Canny(img,img,100,300,3);
	GaussianBlur( img, img, cv::Size(9, 9), 2, 2 );
	// showimg(img);
	HoughCircles(img,circles,CV_HOUGH_GRADIENT,1,img.rows/10,200,50,0,0);
	if(circles.size()==0)
		return 0;
	else{
		*x=*x+circles[circles.size()-1][0];
		*y=*y+circles[circles.size()-1][1];
		return 1;
	}
}

class player
{
public:
  int score,x,y;
  player()
  {
    score=0;
    x=0;
    y=0;
  }
};

class boardgame
{
public:
  cv::Mat board;
  boardgame()
  {
  	board=inputimg();
  	showimg(board);
  }
  int dice_read()
  {
    int x;
    std::cout<<"Enter number on dice:";
    std::cin>>x;
    return x;
  }
  char score(int x,int *score,int *pose_x,int *pose_y)
  {
    if(!x&1){
      (*score)*=2;
      std::cout<<"Moving to nearest red circle\n";
      if(if_circle(board,pose_x,pose_y,2))
        return 1;
    }
    else if(x==1){
      (*score)+=10;
      std::cout<<"Moving to the nearest blue circle\n";
      if(if_circle(board,pose_x,pose_y,0))
        return 1;
    }
    else{
      (*score)+=x;
      std::cout<<"Moving to nearest green circle\n";
      if(if_circle(board,pose_x,pose_y,1))
        return 1;
    }
    return 0;
  }
};

int main()
{
  	boardgame bg;
  	player p1,p2;
    while(1){
      	std::cout<<"\n\n\tPlayer 1 plays\n";
      	//std::cout<<"Pos. of Player1:"<<p1.x<<p1.y;
      	if(bg.score(bg.dice_read(),&p1.score,&p1.x,&p1.y)){
         	std::cout<<"Player 1 moves to the next circle\nGame continues\n";
        }
      	else{
        	std::cout<<"Player 1 has no choice of circle to move.\nPlayer 1 wins\n";
          	return 0;
      	}
      	std::cout<<"\n\tPlayer 2 plays\n";
      	//std::cout<<"Pos. of Player2:"<<p2.x<<p2.y;
      	if(bg.score(bg.dice_read(),&p2.score,&p2.x,&p2.y))
        	std::cout<<"Player 2 moves to the next circle\nGame continues\n";
      	else{
        	std::cout<<"Player 2 has no choice of circle to move.\nPlayer 2 wins\n";
          	return 0;
      	}
    }
  	return 0;
}
