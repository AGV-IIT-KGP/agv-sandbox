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

class pqueue
{
private:
	point *q;
	int rear,lim;
public:
	pqueue(int n){
		rear=0;
		q=new point[n];
		lim=n;
	}
	void enque(point a){
		if(rear<lim){
			int i,index=0;
			point temp_max;
			for(i=0;i<rear && q[i].priority<=a.priority;++i);
			for(;i<rear;++i)
				q[i]=q[i+1];
			rear++;
		}
		else
			std::cout<<"Overflow";
	}
	point deque()
	{
		if(rear==0)
			std::cout<<"Empty queue";
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
	int i,j;
	int **array;
public:
	int size;
	map(int n){
		array = new int*[n];
		for(i=0;i<n;++i)
    		array[i] = new int[n];
		size=n;
	}
	void clear(){
		for(i=0;i<size;++i)
			for(j=0;j<size;++j)
				array[i][j]=0;
	}
	void set(point p,int a){
		array[p.x][p.y]=a;
	}
	int look(int x,int y){
		return array[x][y];
	}
	void print(){
		for(i=0;i<size;++i){
			for(j=0;j<size;++j)
				std::cout<<array[i][j]<<"\t";
			std::cout<<std::endl<<std::endl;
		}
	}
};