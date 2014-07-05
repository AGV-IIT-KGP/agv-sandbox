#include <stdio.h>
#include <highgui.h>
#include <cv.h>
#include <cxcore.h>
#include <stdio.h>
#include <stdlib.h>
 
#define PIX(img,i,j,k) (((uchar*)img->imageData)[(i)*img->widthStep+(j)*img->nChannels+(k)])
typedef struct node
{
int x;
int y;
struct node *next;
}node;
 
node *rear,*front;
 
int isEmpty()
{
if(front==NULL)
return 1;
else return 0;
}
void enqueue(int x,int y)
{
node* t;
t=(node*)malloc(sizeof(node));
t->x=x;
t->y=y;
t->next=NULL;
if(isEmpty())
{
front=t;
rear=front;
}
else{
rear->next=t;
rear=t;
rear->next=NULL;
}
}
void queuefront(int *x,int *y)
{
*x=front->x;
*y=front->y;
return;
}
void dequeue()
{
node* t;
if(isEmpty())
{
printf("Queue Underflow\n");
return;
}
t=front;
front=t->next;
free(t);
}
 
IplImage* img;
IplImage* gray;
 
int** blobDetection(IplImage *img,int *count)
{
int i,j,k,l,x,y;
*count=0;
int height = img->height;
int width = img->width;
int **visited;
visited = (int**)malloc(height*sizeof(int*));
for(i=0;i<img->height;i++)
visited[i]=(int*)malloc(img->width*sizeof(int));
for(i=0;i<img->height;i++)
for(j=0;j<img->width;j++)
visited[i][j]=-1;
for(i=1;i<img->height-1;i++)
for(j=1;j<img->width-1;j++)
{
if(PIX(img,i,j,0)==0)
{
if(visited[i][j]==-1)
{
*count=*count +1;
front=NULL;
enqueue(i,j);
queuefront(&x,&y);
while(!isEmpty())
{
queuefront(&x,&y);
//printf("(%d,%d),(%d)",x,y,visited[x][y]);
dequeue();
for(k=x-1;k<=x+1;k++)
for(l=y-1;l<=y+1;l++)
{
if(PIX(img,k,l,0)==0 && visited[k][l]==-1)
{
enqueue(k,l);
visited[k][l]=*count;
}
}
visited[x][y]=*count;
}
}
}
}
//printf("%d\n",*count);
return visited;
}
 
 
void hough()
{
IplImage *frame,*output;
//cvWaitKey(10000);
int thresh=127;
//cvNamedWindow("win",CV_WINDOW_AUTOSIZE);
cvNamedWindow("window",CV_WINDOW_AUTOSIZE);
cvShowImage("window",gray);
output=cvCreateImage(cvGetSize(gray),IPL_DEPTH_8U,1);
int height,width;
height=gray->height;
width=gray->width;
int** mat;
int diag;
diag=(int)(sqrt(height*height + width*width));
int angle=360;
int step=2;
int i,j;
CvScalar pixel;
 
mat=(int**)(malloc(diag*sizeof(int*)));
for(i=0;i<diag;i++)
{
mat[i]=(int *)(malloc(angle*sizeof(int)));
}
for(i=0;i<diag;i++)
{
for(j=0;j<angle;j++)
{
mat[i][j]=0;
}
}
int distance=0;
int temp;
 
for(i=0;i<gray->height;i++)
{
for(j=0;j<gray->width;j++)
{
CvScalar pixel;
pixel=cvGet2D(gray,i,j);
if(pixel.val[0]==0)
{
for(temp=0;temp<360;temp++)
{
distance=(int)(fabs(j*cos(temp*3.14/180.0)+i*sin(temp*3.14/180.0)));
mat[distance][temp]++;
}
}
}
}
 
int x;
int count=0;
thresh=100;
cvCreateTrackbar("Thresh","window",&thresh,500);
while(1)
{
pixel.val[0]=0;
for(x=0;x<gray->width;x++)
{
int y;
for(y=0;y<gray->height;y++)
{
cvSet2D(output,y,x,pixel);
}
}
pixel.val[0]=255;
for(i=0;i<diag;i++)
{
for(j=0;j<360;j++)
{
if(mat[i][j]>thresh)
{
count++;
//printf("%d %d\n",i,j);
for(x=0;x<gray->width;x++)
{
int y;
y=(int)(-(1.0)/tan(j*3.14/180.0)*x + i/sin(j*3.14/180.0));
if(y>=0 && y<gray->height)
{
//printf("%d %d\n",y,x);
cvSet2D(output,y,x,pixel);
}
}
}
}
}
cvShowImage("my_win",output);
if(cvWaitKey(33)==27 || thresh==20)
break;
}
//cvReleaseImage(&output);
//printf("%d\n",count);
//cvShowImage("my_win",output);
//cvWaitKey(0);
cvDestroyAllWindows();
return;
}
void function(int **data,int counts, double count_x[], double count_y[]) //function to detect the shapes
{
 
cvNamedWindow("win",0); //create window in function
int k,l,count;
CvScalar pixel,pix,pix2; //structure to store four values
int i,j,t;
for(count=1;count<=counts;count++)
{
int c=0;
gray=cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
for(i=1;i<img->height-1;i++)
{
for(j=1;j<img->width-1;j++)
{
pixel.val[0]=255;
cvSet2D(gray,i,j,pixel);
int min=count;
int max=-1;
for(k=i-1;k<=i+1;k++)
{
for(l=j-1;l<=j+1;l++)
{
//pix=cvGet2D(img,k,l); //Getting pixel from loaded image
/* cvGet2D(<image name>,<x coord>,<y coord>) */
if(min>data[k][l])
min=data[k][l];
if(data[k][l]<=count && max<data[k][l])
max=data[k][l];
}
}
if((max-min)==count+1)
{
c++;
pixel.val[0]=0; //Threshold
}
else
pixel.val[0]=255;
// printf("HERE\n");
cvSet2D(gray,i,j,pixel); //Set pixel
/*cvSet2D(<image name>,<x coord>,<y coord>, <name of pixel>) */
}
}
cvShowImage("win",gray);
//hough();
//Use contours to detect number of edges
CvSeq* contours; //hold the pointer to a contour in the memory block
CvSeq* result; //hold sequence of points of a contour
CvMemStorage *storage = cvCreateMemStorage(0); //storage area for all contours
 
//finding all contours in the image
cvFindContours(gray, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));
 
//iterating through each contour
 
result = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);
 
 
printf("No. of contours is %d \n",result->total);
if(result->total==3)
printf("Triangle\n");
else if(result->total==4)
printf("Square\n");
else if (result->total==8)
printf("Circle\n");
else
printf("Arbit\n");
 
 
//shaped(count_x[count],count_y[count],count);
cvReleaseImage(&gray);
cvWaitKey(0);
}
 
}
 
void binary_convert(IplImage *img) //Convert Image to binary
{
int i,j;
CvScalar pixel;
for(i=0;i<img->height;i++)
{
for(j=0;j<img->width;j++)
{
pixel=cvGet2D(img,i,j);
if(pixel.val[0]>100)
{
PIX(img,i,j,0)=255;
}
else
{
PIX(img,i,j,0)=0;
}
}
}
//cvNamedWindow("win",0);
//cvShowImage("win",img);
//cvWaitKey(0);
}
 
void centroid(int** output,int count,double count_x[],double count_y[]) //Centroid
{
int i,j;
 
double count_pixel[count+1];
 
for(i=0;i<img->height;i++)
{
for(j=0;j<img->width;j++)
{
int value;
value=output[i][j];
if(value!=-1)
{
count_x[value]+=j;
count_y[value]+=i;
count_pixel[value]++;
}
}
}
for(i=1;i<count+1;i++)
{
count_x[i]/=count_pixel[i];
count_y[i]/=count_pixel[i];
}
for(i=1;i<count+1;i++)
{
printf("For blob %d centroid is, x = %lf and y = %lf\n",i,count_x[i],count_y[i]);
//count_y[i]/=count_pixel[i];
}
}
int main()
{
 
IplImage* out;
int** output=NULL;
int count=0;
int i,j;
img=cvLoadImage("Untitled.jpg",0);
//out=cvCreateImage(cvGetSize(img),img->depth,1);
binary_convert(img); //Convert image to binary
 
output=blobDetection(img,&count); //Blob detection
 
printf("count = %d\n",count);
cvShowImage("window2",img);
double* count_x;
double* count_y;
 
count_x=(double* )(malloc(count*sizeof(double)));
count_y=(double* )(malloc(count*sizeof(double)));
centroid(output,count, count_x, count_y);
function(output,count,count_x, count_y); //Centroid Callback function
cvWaitKey(0);
return 0;
}