#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
using namespace std;

class image{
public:
cv::Mat img;
int** A,mark,*count_x,*count_y;
image(int a){
img=cv::imread("/home/arnatubai/Desktop/circles2.png",CV_LOAD_IMAGE_COLOR);
A=new int*[img.rows];
	 for(int i=0;i<img.rows;i++)A[i]=new int[img.cols];	
	 for(int i=0;i<img.rows;i++){
		 for(int j=0;j<img.cols;j++){
			 A[i][j]=-1;
		 }}
		 
		 mark=0;
	cout<<A[10][10]<<endl;
}
cv::Mat game_binary(cv::Mat img);
//int** allocate_A();
cv::Mat qblobdetect(cv::Mat& bin);
void centroid(cv::Mat qblob,int* count_pix);
void process_image();
};
