#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "image.h"

struct ind{int x;int y;
struct ind* next;};
struct ind *front,*rear;


void enqueue(int x,int y){
struct ind* n;
n=(struct ind*)malloc(sizeof(struct ind));
n->x=x;
n->y=y;
n->next=NULL;
if(front==NULL){front=n;rear=front;}
else {rear->next=n;rear=n;}
}
void dequeue(){
	struct ind* t;
	t=front;
	front=t->next;
	free(t);
}
void qfront(int* x,int *y){
	if(front!=NULL){
	*x=front->x;
	*y=front->y;}
	return;
}
int qempty(){
	if(front==NULL)return 1;
	return 0;}




cv::Mat image:: game_binary(cv::Mat img){
	cv::Mat bin(img.rows,img.cols,CV_8UC1,cvScalarAll(0));
	// TODO : img.at<cv::Vec3b>(i, j)[0] = sdfsa
int i,j;	
for(i=0;i<img.rows;i++){
   for(j=0;j<img.cols;j++){
       if( img.at<cv::Vec3b>(i, j)[0]>=235 || img.at<cv::Vec3b>(i, j)[1] >= 235|| img.at<cv::Vec3b>(i, j)[2] >= 235)
       		bin.at<uchar>(i, j) = 255;
       	else bin.at<uchar>(i, j) = 0;
   }

}
return bin;
}


//int* image:: allocate_centroid(int* )

cv::Mat image:: qblobdetect(cv::Mat& bin){
	 //std::cout<<"hello";
	 int i,j,x,y,wd=bin.cols,ht=bin.rows,max_pix_count=0,max_size_index=0;
	 //cout<<" a->"<<A[10][10]<<" "<<mark<<endl;
	 for(i=0;i<ht;i++){
		 for(j=0;j<wd;j++){
			 if(bin.at<uchar>(i,j)==255){
				 if(A[i][j]==-1){
					 mark=mark+1;
				 enqueue(i,j);

				 //A[i][j]=0;
				while(qempty()==0){
				 qfront(&x,&y);
				 int k,l;
				 dequeue();
				 for(k=x-1;k<=x+1;k++){
					 for(l=y-1;l<=y+1;l++){
						 if((k<ht)&&(l<wd)&&(k>=0)&&(l>=0)&&(A[k][l]==-1) && bin.at<uchar>(k,l)==255){
							 enqueue(k,l);
							 A[k][l]=mark;}
					 }}
				 A[x][y]=mark;
				}
			//std::cout<<*mark<<" "<<x<<","<<y<<std::endl;
				 }
			 }
		 }}
		 //cout<<"A->"<<A[10][10]<<endl;

	cv::Mat qblob(bin.rows,bin.cols,CV_8UC3);	 
	 //IplImage* qblobdetect=cvCreateImage(cvGetSize(bin),IPL_DEPTH_8U,3);
	 //int *a;double *c_x,*c_y;
	 
	 //a=(int*)malloc((*mark+1)*sizeof(int));
	 for(i=0;i<ht;i++){
		 for(j=0;j<wd;j++){
			 if(A[i][j]==-1)qblob.at<cv::Vec3b>(i,j)[0]=qblob.at<cv::Vec3b>(i,j)[1]=qblob.at<cv::Vec3b>(i,j)[2]=255;
			else{	 
			 qblob.at<cv::Vec3b>(i,j)[0]=255*sin(A[i][j]);
			 qblob.at<cv::Vec3b>(i,j)[1]=255*cos(A[i][j]);
			 qblob.at<cv::Vec3b>(i,j)[2]=255*(sin(A[i][j])+cos(A[i][j]))/1.5; 
			 }
			 }}
	 
	//centroid(bin,A,*mark,count_x,count_y); 
	 return qblob;
}

void image:: centroid(cv::Mat qblob,int* count_pix){
	
	for(int i=0;i<=mark;i++)count_pix[i]=0;
	for(int i=0;i<=mark;i++)count_x[i]=0;
	for(int i=0;i<=mark;i++)count_y[i]=0;	
	for(int i=0;i<qblob.rows;i++){
		for(int j=0;j<qblob.cols;j++){
				if(A[i][j]!=-1){
					int r=A[i][j];
					count_x[r]+=i;
					count_y[r]+=j;
					count_pix[r]++;
				}
		}
	}
for(int i=1;i<=mark;i++){
	count_x[i]/=count_pix[i];
	count_y[i]/=count_pix[i];
}
}




void image:: process_image(){

cv::namedWindow("C",CV_WINDOW_AUTOSIZE);
cv::imshow("C",img);
cv::waitKey(0);
cv::Mat gray;
cvtColor(img,gray,CV_BGR2GRAY);
cv::imshow("C",gray);
cv::waitKey(0);
cv::Mat bin=game_binary(img);
cv::imshow("C",bin);
cv::waitKey(0);
std::cout<<bin.rows<<","<<bin.cols<<std::endl;
//std::cout<<"haha";
cv::waitKey(0);
//int** A,mark=0;
//A=allocate_A();
cv::Mat qblob=qblobdetect(bin);

std::cout<<mark<<std::endl;
cv::imshow("C",qblob);
cv::waitKey(0);
 count_x=new int[mark+1];
 count_y=new int[mark+1];
int *count_pix=new int[mark+1];
centroid(qblob,count_pix);
for(int i=1;i<=mark;i++){
	std::cout<<i<<":"<<count_x[i]<<","<<count_y[i]<<std::endl;
}
cv::waitKey(0);
cv::destroyWindow("C");
}

/*int main(){
image* real=new image(10);
std::cout<<"hello "<<real->img.rows<<","<<real->img.cols<<endl;
cv::waitKey(0);
real->process_image();
for(int i=1;i<=real->mark;i++){
	std::cout<<i<<":"<<real->count_x[i]<<","<<real->count_y[i]<<std::endl;
}
cv::waitKey(0);

}*/