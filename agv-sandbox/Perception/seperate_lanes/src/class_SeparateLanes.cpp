#include <SeperateLanes/class_SeperateLanes.h>

SeperateLanes::SeperateLanes()
{
cv::Mat image= cv::imread("image.jpg");
cv::Mat formedImage(height,width,CV_8UC3);
distance=0;
}


void SeperateLanes::findDistance()
{


int i,j;

int firstDistance=0,secondDistance=0;

for(i=0;i<heigth;i++)
{
firstDistance=0;
secondDistance=0;

for(j=0;j<width;j++)
{
if(image.at<cv::Vec3b>(i,j)[0]==255)
{
if(firstDistance==0)
firstDistance=j;
else
secondDistance=j;
}
}
if((firstDistance!=0)&&(secondDistance!=0))
break;
}

distance=secondDistance-firstDistance;
}


void SeperateLanes::formImage()
{

int i,j;
int previous=0,thresh=10;

for(i=0;i<height;i++)
{
for(j=0;j<width;j++)
{
if(image.at<cv::Vec3b>(i,j)[0]==255)
{
if(((j-previous)>=(-(distance+thresh)))&&((j-previous)<=(-(distance-thresh)))
{
formedImage.at<cv::Vec3b>(i,j)[0]=255;
formedImage.at<cv::Vec3b>(i,j)[1]=0;
formedImage.at<cv::Vec3b>(i,j)[2]=0;
previous=j;
}
else
{
formedImage.at<cv::Vec3b>(i,j)[0]=255;
formedImage.at<cv::Vec3b>(i,j)[1]=0;
formedImage.at<cv::Vec3b>(i,j)[2]=0;
previous=j;
}
}
}
}
namedWindow("formed Image", CV_WINDOW_AUTOSIZE);
imshow("formed Image", formedImage);
waitKey();
return;
}












