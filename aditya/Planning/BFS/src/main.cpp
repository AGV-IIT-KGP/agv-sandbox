#include <stdio.h>
#include "structs.cpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

cv::Mat img(200,200,CV_8UC1,cvScalarAll(255));
map visit(img.cols,img.rows);
queue que(img.cols*img.rows);
//point origin(rand()%img.cols,rand()%img.rows);
point origin(5,5);
point destn(7,7);
//point destn(rand()%img.cols,rand()%img.rows);

char check(point a)
{
	if(a.x<0 || a.x>=img.rows || a.y<0 || a.y>=img.cols || visit.look(a.x,a.y)==1 || img.at<uchar>(a.x,a.y)<100)
		return 0;
	else
		return 1;
}

void bfs(point** prev)
{
	point a;
	que.enque(origin);
	visit.set(origin,1);
	while(1){
		cv::waitKey(5);
		a=que.deque();
		printf("%d %d\n",a.x,a.y);
		if(a==destn)
			return;
		point p(a.x,a.y-1),q(a.x+1,a.y),r(a.x,a.y+1),s(a.x-1,a.y);
		if(check(p)){
			que.enque(p);
			prev[p.x][p.y]=a;
			visit.set(p,1);
		}
		if(check(q)){
			que.enque(q);
			prev[q.x][q.y]=a;
			visit.set(q,1);
		}
		if(check(r)){
			que.enque(r);
			prev[r.x][r.y]=a;
			visit.set(r,1);
		}
		if(check(s)){
			que.enque(s);
			prev[s.x][s.y]=a;
			visit.set(s,1);
		}
	}
}

void construct_path(point **prev)
{
	point temp=prev[destn.x][destn.y];
	while(!(temp==origin)){
		img.at<uchar>(temp.x,temp.y)=0;
		temp=prev[temp.x][temp.y];
	}
}

int main()
{
	int i;
	printf("Map before BFS traversal\n");
	img.at<uchar>(origin.y,origin.x)=0;
	img.at<uchar>(destn.y,destn.x)=0;
	cv::imshow("window",img);
	cv::waitKey(5000);
	cv::destroyWindow("window");
	printf("hello\n");
	point **prev=new point*[img.cols];
	for(i=0;i<img.cols;++i)
 		prev[i]=new point[img.rows];
	bfs(prev);
	printf("hello\n");
	construct_path(prev);
	printf("Map after BFS traversal\n");
	cv::imshow("window",img);
	cv::waitKey(5000);
	return 0;
}