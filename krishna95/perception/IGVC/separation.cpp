#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/operations.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/stitching/stitcher.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <math.h>
#include <sys/time.h>

using namespace std;
using namespace cv;



Mat Image_Process1(Mat& image,int k){
	Mat channel[3];
	Mat img(image.rows,image.cols,CV_8UC3,cvScalarAll(0));
	Mat img_temp(image.rows,image.cols,CV_8UC1,cvScalarAll(0));
	Mat cimg_temp(image.rows,image.cols,CV_8UC1,cvScalarAll(0));
	split(image,channel);
	/*namedWindow("blue",1);
	imshow("blue",channel[0]);
	namedWindow("green",1);
	imshow("green",channel[1]);
	namedWindow("red",1);
	imshow("red",channel[2]);
	 channel[1]=Mat::zeros(img.rows, img.cols, CV_8UC1);
	 for (int i=0;i<channel[1].rows;i++){
	 	for (int j=0;j<channel[1].cols;j++){
	 		channel[1].at<uchar>(i,j,0)=255;
	 	}
	 }
	 equalizeHist(channel[0],channel[0]);
	 medianBlur(channel[0],channel[0],k);
	 equalizeHist(channel[2],channel[2]);
	medianBlur(channel[2],channel[2],k);
	for (int i=0;i<channel[2].rows;i++){
	 	for (int j=0;j<channel[2].cols;j++){
	 		channel[2].at<uchar>(i,j,0)=255;
	 	}
	 }
	 namedWindow("Eqblue",1);
	imshow("Eqblue",channel[0]);
	namedWindow("Eqred",1);
	imshow("Eqred",channel[2]);
	 merge(channel,3,img);
	 return img;*/
	//namedWindow("hough",1);
	int maxthreshold=255,minthreshold=200,minpoints=20,binthreshold=160,maxpoints=30;
	 equalizeHist(channel[0],channel[0]);
	vector<Vec4i>lines;
	//namedWindow("blue",0);
	//imshow("blue",channel[0]);
	equalizeHist(channel[2],channel[2]);
	
	//namedWindow("red",0);
	//imshow("red",channel[2]);
	int erosion_size = 2;   
	Mat element = cv::getStructuringElement(cv::MORPH_RECT,
                      cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1), 
                      cv::Point(erosion_size, erosion_size) );
	Mat hough(channel[0].rows,channel[0].cols,CV_8UC3,cvScalarAll(0));
	erode(channel[0],channel[0], element);
	namedWindow("blue1",0);
	imshow("blue1",channel[0]);
	erode(channel[2],channel[2], element);
	namedWindow("red1",0);
	imshow("red1",channel[2]);
	//namedWindow("merge",1);
	//namedWindow("Cmerge",1);
	createTrackbar("binthreshold","merge",&binthreshold,255);
	//createTrackbar("minthreshold","cmerge",&minthreshold,255);
	//createTrackbar("maxthreshold","cmerge",&maxthreshold,255);
	//createTrackbar("minpoints","hough",&minpoints,1000);
	//createTrackbar("maxpoints","hough",&maxpoints,1000);
	//while(1)
	{
		
 	
	for (int i=0;i<image.rows;i++){
		for (int j=0;j<image.cols;j++){
			if (channel[0].at<uchar>(i,j)>binthreshold && channel[1].at<uchar>(i,j)>binthreshold)
				img_temp.at<uchar>(i,j)=(channel[0].at<uchar>(i,j)+channel[2].at<uchar>(i,j))/2;
			else
				img_temp.at<uchar>(i,j)=0;
		}
	}
	imshow("merge",img_temp);
	
	Mat hough(channel[0].rows,channel[0].cols,CV_8UC3,cvScalarAll(0));
	Canny(img_temp,cimg_temp,minthreshold,maxthreshold,3);
	imshow("Cmerge",cimg_temp);
	HoughLinesP(cimg_temp,lines,1,CV_PI/180,maxpoints,minpoints,40);
	for (size_t i=0;i<lines.size();i++){
		Vec4i l=lines[i];
		line(hough,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(255,255,255),3,CV_AA);
	}
	imshow("hough",hough);
	waitKey(0);
	}	
return img_temp;
}

void Remove_Obstacle(Mat& im,int k){
	//namedWindow("win",1);
	struct timeval t,c;
	gettimeofday(&t,NULL);
	cv::Mat im_HSV(im.rows,im.cols,CV_8UC3);
	cv::Mat bin(im.rows,im.cols,CV_8UC1);
	cv::Mat bin2(im.rows,im.cols,CV_8UC1);
	cvtColor(im,im_HSV,CV_BGR2HSV);
	int h=0,s=0,v=0;
	int dilation_size = 9;
	cv::Mat element = cv::getStructuringElement( cv::MORPH_ELLIPSE,
                                       cv::Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                       cv::Point( dilation_size, dilation_size ) );
	//cv::imshow("win",im_HSV);
	//cv::createTrackbar("track_HSVh","win",&h,180,NULL);
	//cv::createTrackbar("track_HSVs","win",&s,255,NULL);
	//cv::createTrackbar("track_HSVv","win",&v,255,NULL);


	/*do{
	cv::inRange(im_HSV, cv::Scalar(0,s-1,v-1), cv::Scalar(h,256,255), bin); 
	cv::imshow("win",bin);
	cv::dilate(bin, bin2, element);
	cv::imshow("win1", bin2);

	if(cv::waitKey(33)==27)break;
	}while(1);*/

	cv::inRange(im_HSV, cv::Scalar(0,0,0), cv::Scalar(k,256,255), bin); 
	//cv::imshow("win",bin);
	cv::dilate(bin, bin2, element);
	//cv::imshow("win1", bin2);

	for(int i=0;i<bin2.rows;i++){
		for(int j=0;j<bin2.cols;j++){
			if(bin2.at<uchar>(i,j)==255)
			{
				im.at<cv::Vec3b>(i,j)[0]=im.at<cv::Vec3b>(i,j)[1]=im.at<cv::Vec3b>(i,j)[2]=0;
			}
		}
	}
	cout<<"alpha channel is"<<(int)im_HSV.at<cv::Vec3b>(302,344)[0]<<" "<<(int)im_HSV.at<cv::Vec3b>(302,344)[1]<<" "<<(int)im_HSV.at<cv::Vec3b>(302,344)[2]<<endl;
	cout<<"alpha channel is"<<(int)im_HSV.at<cv::Vec3b>(376,74)[0]<<" "<<(int)im_HSV.at<cv::Vec3b>(376,74)[1]<<" "<<(int)im_HSV.at<cv::Vec3b>(376,74)[2]<<endl;
	gettimeofday(&c,NULL);
	// double td = t.tv_sec + t.tv_usec/1000000.0;
	// double cd = c.tv_sec + c.tv_usec/1000000.0;
	//cout<<"remove obstacles ";
	// std::cout<<"time:"<< 1.0/(cd-td) <<std::endl;
	return ;
}


int main(int argc, char* argv[]){
	struct timeval t,c;
	gettimeofday(&t,NULL);
	Mat sample=imread(argv[1],1);
	Mat final1 = sample -sample;
	Mat final2 = final1.clone();
	cout<<"hello";
	namedWindow("source",1);
	imshow("source",sample);
	Remove_Obstacle(sample,10);
	final1 = sample;
	 namedWindow("final1",1);
	 imshow("final1",final1);
	 final2=Image_Process1(final1,7);
	//sample=Image_Process2(sample,7);
	gettimeofday(&c,NULL);
	double td = t.tv_sec + t.tv_usec/1000000.0;
	double cd = c.tv_sec + c.tv_usec/1000000.0;
	std::cout<<"time:"<< 1.0/(cd-td) <<std::endl;
		namedWindow("final2",1);
	imshow("final2",final2);
	waitKey(0);
}








