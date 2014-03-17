#include <iostream>
#include "structs.cpp"

map m(7);
queue q(49);
pqueue pq(49);
point origin(1,5,0);
point destn(5,1,0);

void bfs(point origin,point destn, map m)
{
	q.enque(origin);
	while(1){
		
	}
}

void create_map()
{
	m.clear();
	point p(2.2,0),q(3,4,0),r(4,1,0),s(4,3,0),t(4,4,0);
	m.set_obs(p);
	m.set_obs(q);
	m.set_obs(r);
	m.set_obs(s);
	m.set_obs(t);
}

int main()
{
	create_map();	
}