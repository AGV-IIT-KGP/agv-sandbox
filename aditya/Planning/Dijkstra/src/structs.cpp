#include<iostream>
#define INFINITY 9999

class node
{	
public:
	int visit,distn;
	node(){
		visit=-1;
		distn=INFINITY;
	}
	/*bool operator== (point a){
		if(x==a.x && y==a.y)
			return 1;
		return 0;
	}*/
};

class graph
{
private:
	int n,edges;
	node *arr;
public:
	int** adj_list;
	graph(){
		std::cout<<"Enter number of nodes:";
		std::cin>>n;
		arr=new node[n];
		std::cout<<"Enter number of edges:";
		std::cin>>edges;
		adj_list = new int*[n];
		for(int i=0;i<n;++i)
    		adj_list[i]=new int[n];
    	for(int i=0;i<n;i++)
    		for(int j=0;j<n;j++)
    			adj_list[i][j]=0;
		int origin,dest,weight;
		std::cout<<"Enter the connecting nodes and weight of each edge:"<<std::endl;
		for(int i=0;i<edges;i++){
			std::cin>>origin>>dest>>weight;
			adj_list[origin][dest]=weight;
			adj_list[dest][origin]=weight;
		}
	}
	int get_size(){
		return n;
	}
	node* get_node(int index){
		return &arr[index];
	}
	void set_distn(int index,int b){
		if(arr[index].distn>(adj_list[index][b]+arr[b].distn))
			arr[index].distn=adj_list[index][b];
	}
};

class pqueue
{
private:
	int rear,lim,*q;
	graph *g;
public:
	pqueue(int n, graph *pointer){
		rear=0;
		q=new int[n];
		lim=n;
		g=pointer;
	}
	void enque(int p,int p_prev){
		if(rear<lim && g->get_node(p)->visit==-1){
			int i,j;
			for(i=0;i<rear && g->get_node(i)->distn>=g->get_node(p)->distn;++i);
			for(j=rear;j>i;--j)
				q[j]=q[j-1];
			q[j]=p;
			rear++;
			g->get_node(p)->visit=p_prev;
		}
	}
	int deque(){
		if(!rear)
			std::cout<<"Empty queue";
		return q[--rear];
	}
	void print(){
		for(int i=0;i<rear;++i)
			std::cout<<q[i];
		std::cout<<std::endl;
	}
};