#include <iostream>
#include <cmath>
#include <queue>
#include <ctime>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

#define UNVISITED 0
#define OPEN 1
#define CLOSE 2
#define DIMENSION 400

using namespace std;

int dx[]={1, 1, 0, -1, -1, -1, 0, 1};
int dy[]={0, 1, 1, 1, 0, -1, -1, -1};
int cost[]={10, 14, 10, 14, 10, 14, 10, 14};
int s_x,s_y,d_x,d_y;
cv::Mat img;

class vertex
{
public:
	int x,y,obstruction;
	int g,h;
	vertex* parent;
	vertex(int xcoord, int ycoord, uchar img)
	{
		x=xcoord;
		y=ycoord;
		parent=NULL;
		h=fabs(x-d_x)*10+fabs(y-d_y)*10;
		obstruction=(img<50?1:0);
	}
	int get_f()
	{
		return g+h;
	}
	void set_parent(vertex *p)
	{
		parent=p;
	}
};

class Compare
{
public:
    bool operator() (vertex* &lhs, vertex* &rhs)
    {
        if(lhs->get_f()>rhs->get_f()) return true;
        return false;
    }
};

void create_map(vertex ***map)
{
    for(int i=0;i<DIMENSION;i++){
    	map[i] = new vertex*[DIMENSION];
    	for(int j=0; j<img.cols; ++j){
    		map[i][j]= new vertex(i,j,img.at<uchar>(i,j));
    	}
    }
}

void path(vertex*** map)
{
	vertex* next= map[d_x][d_y]->parent;
	while(next->x!=s_x && next->y!=s_y){
		img.at<uchar>(next->x,next->y)=150;
		next=next->parent;
	}	
}

void ASTAR(vertex*** map, int state[DIMENSION][DIMENSION])
{
	clock_t begin = clock();
    priority_queue<vertex*, vector<vertex*>, Compare> Q;
    map[s_x][s_y]->g=0;
    map[s_x][s_y]->h=0;
    state[s_x][s_y]=OPEN;
    Q.push(map[s_x][s_y]);
    while(!Q.empty() )
    {
        vertex* t = Q.top();
        Q.pop();
        //cout<<t->x<<t->y;
        if(t->x==d_x && t->y==d_y){
        	//cout<<"Found"<<t->x<<t->y;
        	clock_t end = clock();
  			cout<<double(end - begin) / CLOCKS_PER_SEC<<" seconds\n";
        	path(map);
            return;
        }
        state[t->x][t->y]=CLOSE;
        for (int i = 0; i<8; i++){
        	int xdx=t->x+dx[i];
        	int ydy=t->y+dy[i];
            if(xdx<0 || ydy<0 || xdx>=DIMENSION || ydy>=DIMENSION)
                continue;
            if(map[xdx][ydy]->obstruction==1 || state[xdx][ydy]==CLOSE)
                continue;
            if(state[xdx][ydy]==UNVISITED){
            	map[xdx][ydy]->g = t->g + cost[i];
            	map[xdx][ydy]->parent=t;
            	Q.push(map[xdx][ydy]);
           	}
           	else{
           		int temp_g=t->g+cost[i];
           		if( map[xdx][ydy]->g > temp_g ){
   					map[xdx][ydy]->g = temp_g;
   					map[xdx][ydy]->parent=t;             
            	}
        	}
    	}
	}
}

int main()
{
    img=cv::imread("./image.jpg",1);
    //cout<<img.rows<<img.cols;
    cout<<"Enter source pixel"<<endl;
    cin>>s_x>>s_y;
    cout<<"Enter destination pixel"<<endl;
    cin>>d_x>>d_y;
    int state[DIMENSION][DIMENSION];	//0-none,1-open,2-close
    for(int i=0;i<DIMENSION;i++){
    	for(int j=0; j<DIMENSION; ++j){
    		state[i][j]=UNVISITED;
    	}
    }
    vertex ***map = new vertex**[DIMENSION];;
    create_map(map);
    cv::imshow("window",img);
    cv::waitKey(0);
    //cv::destroyAllWindows();
  	ASTAR(map,state);
    cv::imshow("window",img);
    cv::waitKey(0);
    return 0;
}