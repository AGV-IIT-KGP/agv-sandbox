#include <iostream>
#include "structs.cpp"

map m(7);
map visit(7);
point origin(1,5);
point destn(5,1);

int recurse(point a)
{
	if(a.x<0 || a.x>=m.size || a.y<0 || a.y>=m.size || visit.look(a.x,a.y)==1 || m.look(a.x,a.y)==-1)
		return 0;
	visit.set(a,1);
	if(a == destn){
		return 1;
	}
	else{
		point p(a.x,a.y-1),q(a.x+1,a.y),r(a.x,a.y+1),s(a.x-1,a.y);
		if(recurse (p)){
			m.set(a,1);
			return 1;
		}
		if(recurse (q)){
			m.set(a,1);
			return 1;
		}
		if(recurse (r)){
			m.set(a,1);
			return 1;
		}
		if(recurse (s)){
			m.set(a,1);
			return 1;
		}
	}
	return 0;
}

void create_map()
{
	m.clear();
	visit.clear();
	point p(2,2),q(3,4),r(4,1),s(4,3),t(4,4),u(5,4),v(3,0);
	m.set(p,-1);
	m.set(q,-1);
	m.set(r,-1);
	m.set(s,-1);
	m.set(t,-1);
	m.set(u,-1);
	m.set(v,-1);
	m.set(origin,2);
	m.set(destn,2);
}

int main()
{
	create_map();	
	std::cout<<"Map before DFS traversal\n(-1=obstructions)\n(2=origin/destination)\n";
	m.print();
	// visit.print();
	recurse(origin);
	m.set(origin,2);
	std::cout<<"Map after DFS traversal\n";
	m.print();
	// visit.print();
	return 0;
}