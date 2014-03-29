#include <iostream>

class point
{	
public:
	int x,y;
	point(){
		x=0;
		y=0;
	}
	point(int a,int b){
		x=a;
		y=b;
	}
	bool operator== (point a){
		if(x==a.x && y==a.y)
			return 1;
		return 0;
	}
};

class queue
{
private:
	point *q;
	int rear,lim;
public:
	queue(){
		rear=0;
	}
	queue(int n){
		rear=0;
		q=new point[n];
		lim=n;
	}
	void enque(point a){
		if(rear<lim)
			q[rear++]=a;
		else
			std::cout<<"Overflow";
	}
	point deque()
	{
		if(rear==0){
			std::cout<<"Empty queue";
		}
		int i;
		point first=q[0];
		for(i=0;i<rear-1;++i)
			q[i]=q[i+1];
		rear--;
		return first;
	}
};

class map
{
private:
	int i,j,x,y;
	int **array;
public:
	map(int n,int m){
		x=n;
		y=m;
		array = new int*[n];
		for(i=0;i<n;++i)
    		array[i] = new int[m];
	}
	void clear(){
		for(i=0;i<x;++i)
			for(j=0;j<y;++j)
				array[i][j]=0;
	}
	void set(point p,int a){
		array[p.x][p.y]=a;
	}
	int look(int x,int y){
		return array[x][y];
	}
	// void print(){
	// 	for(i=0;i<size;++i){
	// 		for(j=0;j<size;++j)
	// 			std::cout<<array[i][j]<<"\t";
	// 		std::cout<<std::endl<<std::endl;
	// 	}}
};