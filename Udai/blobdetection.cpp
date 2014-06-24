#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>

struct node
{
	int x;
	int y;
};

void BFS(cv::Mat newimg, int**visited, int shape, int i, int j)
{
int front, rear;
node *q = new node[newimg.rows*newimg.cols];
front = rear = 0;
q[front].x = j; 
q[front].y = i;

while(1)
{
	for(int u = q[front].y-1; u<=q[front].y+1; ++u)
		for(int v = q[front].x-1; v<=q[front].x+1; ++v)
			if((u>=0)&&(u<=newimg.rows)&&(v>=0)&&(v<=newimg.cols))
			if((visited[u][v]==-1)&&(newimg.at<uchar>(u,v)==255))
			{
				visited[u][v] = 0;
				rear++;
				q[rear].x = v;
				q[rear].y = u;
			}
	visited[q[front].y][q[front].x] = shape;
	front++;

	if(front>rear){delete q; break;}
}
}