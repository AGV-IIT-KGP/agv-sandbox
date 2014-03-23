#include <iostream>
#include "structs.cpp"

void dijkstra(int origin,int dest,pqueue *que,graph* g)
{
	int a,prev;
	que->enque(origin,-1);
	prev=origin;
	while(1){
		//que->print();
		a=que->deque();
		g->set_distn(a,prev);
		if(a==dest){
			std::cout<<"Minimum distance is: "<<g->get_node(a)->distn<<std::endl;
			return;
		}
		for(int i=0;i<g->get_size();++i){
			if(g->adj_list[i][a])
				que->enque(i,a);
		}
		//que->print();
		prev=a;
	}
}

int main()
{
	int n_origin,n_dest;
	graph g;
	pqueue que(g.get_size(),&g);
	std::cout<<"Enter the origin node index: ";
	std::cin>>n_origin;
	std::cout<<"Enter the destination node index: ";
	std::cin>>n_dest;
	dijkstra(n_origin,n_dest,&que,&g);
	return 0;
}