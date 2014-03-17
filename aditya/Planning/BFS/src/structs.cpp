#include <iostream>

class point
{	
public:
	int x,y;
	float priority;
	point(){
		x=0;
		y=0;
		priority=0;
	}
	point(int a,int b,float c){
		x=a;
		y=b;
		priority=c;
	}
	void display(){
		std::cout<<x<<y;
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
	point pop()
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
	point pop()
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
	int size,i,j;
	int **array;
public:
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
	void set_obs(point p){
		array[p.x][p.y]=-1;
	}
	void print(){
		for(i=0;i<size;++i){
			for(j=0;j<size;++j)
				std::cout<<array[i][j]<<"\t";
			std::cout<<std::endl;
		}
	}
};

int main()
{
	queue x;
	x.init(5);
	point p(1,1,1),q(2,2,2),r(3,3,3),s(4,4,4),t(0,0,0),pop;
	x.enque(p);
	x.enque(q);
	x.enque(r);
	x.enque(s);
	x.enque(t);
	pop=x.pop();
	pop.display();
	return 0;
}