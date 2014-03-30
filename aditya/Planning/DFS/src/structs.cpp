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
	bool operator== (point b){
		if(x==b.x && y==b.y)
			return 1;
		return 0;
	}
	void display(){
		std::cout<<x<<y;
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
	void set(point p,int x){
		array[p.x][p.y]=x;
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
