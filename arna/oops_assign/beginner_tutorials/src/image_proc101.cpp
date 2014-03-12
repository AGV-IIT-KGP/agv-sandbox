#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

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




cv::Mat game_binary(cv::Mat img){
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

cv::Mat qblobdetect(cv::Mat& bin,int* mark,int** A){
	 //std::cout<<"hello";
	 int i,j,x,y,wd=bin.cols,ht=bin.rows,max_pix_count=0,max_size_index=0;
	 
	 for(i=0;i<ht;i++){
		 for(j=0;j<wd;j++){
			 if(bin.at<uchar>(i,j)==255){
				 if(A[i][j]==-1){
					 *mark=*mark+1;
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
							 A[k][l]=*mark;}
					 }}
				 A[x][y]=*mark;
				}
			std::cout<<*mark<<" "<<x<<","<<y<<std::endl;	 }
			 }
		 }}

	cv::Mat qblob(bin.rows,bin.cols,CV_8UC3);	 
	 //IplImage* qblobdetect=cvCreateImage(cvGetSize(bin),IPL_DEPTH_8U,3);
	 //int *a;double *c_x,*c_y;
	 
	 //a=(int*)malloc((*mark+1)*sizeof(int));
	 for(i=0;i<ht;i++){
		 for(j=0;j<wd;j++){
			 //if(A[i][j]!=-1)a[A[i][j]]++;
				 //IMGDATA(qblobdetect,i,j,0)=IMGDATA(qblobdetect,i,j,1)=IMGDATA(qblobdetect,i,j,2)=255;
			 //else{
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




int main(){
cv::Mat img=cv::imread("/home/arnatubai/Desktop/circles.jpg",CV_LOAD_IMAGE_COLOR);
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

int** A,mark=0;
A=new int*[bin.rows];
	 for(int i=0;i<bin.rows;i++)A[i]=new int[bin.cols];	
	 for(int i=0;i<bin.rows;i++){
		 for(int j=0;j<bin.cols;j++){
			 A[i][j]=-1;
		 }}
cv::Mat qblob=qblobdetect(bin,&mark,A);

std::cout<<mark<<" "<<A[100][125]<<std::endl;
cv::imshow("C",qblob);
count_x=new int[count];
count_y=new int[count];
centroid()
cvWaitKey(0);
}