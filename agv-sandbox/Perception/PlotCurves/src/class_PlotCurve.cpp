PlotCurve::PlotCurve(cv::Mat image)
{
image=image;
cv::Mat formedImage(height,width,CV_8UC1);
points1={0};
points2={0};
}

void PlotCurve::findPoints()
{
int i,j,k=1,sumX1=0,sumY1=0,noOfPts2=0,noOfPts1=0,sumX2=0,sumY2=0;

for(i=0;i<height;i++)
{
for(j=0;j<width;j++)
{
if((image.at<cv::Vec3b>(i,j)[0]==255)&&(image.at<cv::Vec3b>(i,j)[1]==0)&&(image.at<cv::Vec3b>(i,j)[2]==0))
{
sumX1+=i;
sumY1+=j;
noOfPts1++;
}
else if((image.at<cv::Vec3b>(i,j)[0]==0)&&(image.at<cv::Vec3b>(i,j)[1]==255)&&(image.at<cv::Vec3b>(i,j)[2]==0))
{
sumY1+=i;
sumY2+=j'
noOfPts2++;
}
}
if(i==((height*k)/5))
{
points1[k-1].x=sumX1/noOfPts1;
points2[k-1].y=sumY1/noOfPts2;
k++;
}
}
return;
}

int PlotCurve::findY(int x, Node p)
{

int y;

y= (p[0].y)*(x-p[1].x)*(x-p[2].x)*(x-p[3].x)*(x-p[4].x)/((p[0].x-p[1].x)*(p[0].x-p[2].x)*(p[0].x-p[3].x)*(p[0].x-p[4].x)) + 
(p[1].y)*(x-p[0].x)*(x-p[2].x)*(x-p[3].x)*(x-p[4].x)/((p[1].x-p[0].x)*(p[1].x-p[2].x)*(p[1].x-p[3].x)*(p[1].x-p[4].x)) +
 (p[2].y)*(x-p[1].x)*(x-p[0].x)*(x-p[3].x)*(x-p[4].x)/((p[2].x-p[0].x)*(p[2].x-p[1].x)*(p[2].x-p[3].x)*(p[2].x-p[4].x)) +
(p[3].y)*(x-p[1].x)*(x-p[2].x)*(x-p[0].x)*(x-p[4].x)/((p[3].x-p[0].x)*(p[3].x-p[1].x)*(p[3].x-p[2].x)*(p[3].x-p[4].x)) +
(p[4].y)*(x-p[1].x)*(x-p[2].x)*(x-p[3].x)*(x-p[0].x)/((p[4].x-p[0].x)*(p[4].x-p[1].x)*(p[4].x-p[2].x)*(p[4].x-p[3].x));

return y;
}

void PlotCurve::drawCurve()
{

int i;
for(i=0;i<height;i++)
{
y=PlotCurve(x,points1);
formedImage.at<cv::Vec3b>(x,y)[0]=255;
formedImage.at<cv::Vec3b>(x,y)[1]=0;
formedImage.at<cv::Vec3b>(x,y)[2]=0;
y=PlotCurve(x,points2);
formedImage.at<cv::Vec3b>(i,j)[0]=255;
formedImage.at<cv::Vec3b>(i,j)[1]=0;
formedImage.at<cv::Vec3b>(i,j)[2]=0;
}

namedWindow("formed Image", CV_WINDOW_AUTOSIZE);
imshow("formed Image", formedImage);
waitKey();
return;
}











