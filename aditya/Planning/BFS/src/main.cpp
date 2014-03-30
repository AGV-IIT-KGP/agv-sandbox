#include <iostream>
#include "structs.cpp"

map m(7);
map visit(7);
queue que(49);
point origin(1,5);
point destn(5,1);

char check(point a)
{
if(a.x<0 || a.x>=m.size || a.y<0 || a.y>=m.size || visit.look(a.x,a.y)==1 || m.look(a.x,a.y)==-1)
return 0;
else
return 1;
}

void bfs(point ** prev)
{
point a;
que.enque(origin);
visit.set(origin,1);
while(1){
a=que.deque();
if(a==destn)
return;
point p(a.x,a.y-1),q(a.x+1,a.y),r(a.x,a.y+1),s(a.x-1,a.y);
if(check(p)){
que.enque(p);
prev[p.x][p.y]=a;
visit.set(p,1);
}
if(check(q)){
que.enque(q);
prev[q.x][q.y]=a;
visit.set(q,1);
}
if(check(r)){
que.enque(r);
prev[r.x][r.y]=a;
visit.set(r,1);
}
if(check(s)){
que.enque(s);
prev[s.x][s.y]=a;
visit.set(s,1);
}
}
}

void construct_path(point **prev)
{
point temp=prev[destn.x][destn.y];
while(!(temp==origin)){
m.set(temp,1);
temp=prev[temp.x][temp.y];
}
}

void create_map()
{
m.clear();
visit.clear();
point p(2,2),q(3,4),r(4,1),s(4,3),t(4,4);
m.set(p,-1);
m.set(q,-1);
m.set(r,-1);
m.set(s,-1);
m.set(t,-1);
m.set(origin,2);
m.set(destn,2);
}

int main()
{
int i;
create_map();
point **prev=new point*[7];
for(i=0;i<7;++i)
  prev[i]=new point[7];
std::cout<<"Map before BFS traversal\n(-1=obstructions)\n(2=origin/destination)\n";
m.print();
bfs(prev);
construct_path(prev);
std::cout<<"Map after BFS traversal\n";
m.print();
return 0;
}