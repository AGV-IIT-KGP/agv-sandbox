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
int cost[]={10, 20, 10, 20, 10, 20, 10, 20};
int s_x,s_y,d_x,d_y;
cv::Mat img(DIMENSION,DIMENSION,CV_8UC1,cvScalarAll(255));

class vertex
{
public:
	int x,y,obstruction;
	int g,h;
	vertex* parent;
	inline vertex(int xcoord, int ycoord, uchar img)
	{
		x=xcoord;
		y=ycoord;
		parent=NULL;
		h=fabs(x-d_x)*10+fabs(y-d_y)*10;
		//h=(sqrt7((x-d_x)*(x-d_x)+(y-d_y)*(y-d_y)))*10;
		obstruction=(img<50?1:0);
	}
	inline int get_f()
	{
		return g+h;
	}
	inline void set_parent(vertex *p)
	{
		parent=p;
	}
};

class Compare
{
public:
    inline bool operator() (vertex* &lhs, vertex* &rhs)
    {
        if(lhs->get_f()>rhs->get_f()) return true;
        return false;
    }
};

inline void create_map(vertex ***map)
{
    for(int i=0;i<DIMENSION;i++){
    	map[i] = new vertex*[DIMENSION];
    	for(int j=0; j<img.cols; ++j){
    		map[i][j]= new vertex(i,j,img.at<uchar>(i,j));
    	}
    }
}

inline void delete_map(vertex ***map)
{
    for(int i=0;i<DIMENSION;i++){
    	for(int j=0; j<img.cols; ++j){
    		delete map[i][j];
    	}
    	delete map[i];
    }
    delete map;
}

inline void path(vertex*** map,cv::Mat* image)
{
	vertex* next= map[d_x][d_y]->parent;
	while(next->x!=s_x && next->y!=s_y){
		image->at<uchar>(next->x,next->y)=150;
		next=next->parent;
	}	
}

inline void ASTAR(vertex*** map, int state[DIMENSION][DIMENSION])
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
        if(t->x==d_x && t->y==d_y){
        	clock_t end = clock();
  			cout<<double(end - begin) / CLOCKS_PER_SEC<<" seconds\n";
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

cv::Mat distance_transform(cv::Mat orig)
{
	/*cv::imshow("window",orig);
	cv::waitKey(0);*/
	cv::distanceTransform(orig, orig, CV_DIST_L1, 3);
	normalize(orig, orig, 0, 255, cv::NORM_MINMAX, CV_8UC1);
	/*cv::imshow("window",orig);
	cv::waitKey(0);*/
	for(int i=0; i<DIMENSION; ++i){
		for(int j=0; j<DIMENSION; ++j){
			if(orig.at<uchar>(i,j)<22)
				orig.at<uchar>(i,j)=255;
			else
				orig.at<uchar>(i,j)=0;
		}
	}
	orig=255-orig;
	/*cv::imshow("window",orig);
	cv::waitKey(0);
	*/
	return orig;
}

int main()
{
    cv::circle(img, cv::Point(100, 125), 32, 0, -1, CV_AA);
    cv::circle(img, cv::Point(299, 256), 60, 0, -1, CV_AA);
    cv::circle(img, cv::Point(155, 240), 32, 0, -1, CV_AA);
    cv::imshow("window",img);
    cv::waitKey(70);
    cv::Mat orig=img.clone();
    img=distance_transform(orig);
    cout<<"Enter source pixel"<<endl;
    cin>>s_x>>s_y;
    cout<<"Enter destination pixel"<<endl;
    cin>>d_x>>d_y;
    if(img.at<uchar>(s_x,s_y)<50 || img.at<uchar>(d_x,d_y)<50){
    	cout<<"Wrong input. Point in obstruction area\n";
    	return 0;
    }
    int state[DIMENSION][DIMENSION];	//0-none,1-open,2-close
    for(int i=0;i<DIMENSION;i++){
    	for(int j=0; j<DIMENSION; ++j){
    		state[i][j]=UNVISITED;
    	}
    }
    vertex ***map = new vertex**[DIMENSION];;
    create_map(map);
  	ASTAR(map,state);
  	path(map,&orig);
    cv::imshow("window",orig);
    cv::waitKey(0);
    delete_map(map);
    return 0;
}