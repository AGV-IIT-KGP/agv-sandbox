#include <iostream>
#include <queue>
#include <stdio.h>
using namespace std;
struct node
{
	int i;
	int cweight;
};

class CompareWeight
{
	public:
	bool operator() (node& lhs, node& rhs) 
	{
		if (lhs.cweight>rhs.cweight) return true;
		return false;
	}
};

int main()
{	
	int j,l,n,s,e,present;
	node start,current,next;
	n=8;
	int k[n][n], past[n],flag[n];
	for(j=0;j<n;j++)
		flag[j]=-1;
	priority_queue <node, vector<node>, CompareWeight> pq;
	
	cout<<"Start=";
	cin>>s;
	cout<<"End=";
	cin>>e;
	for(j=0;j<n;j++)
	{
		for(l=0;l<n;l++)
		{
			k[j][l]=-1;
		}
	}
	
	k[0][1]=20;
	k[0][3]=80;
	k[0][6]=90;
	k[1][5]=10;
	k[2][3]=10;
	k[2][5]=50;
	k[2][7]=20;
	k[3][2]=10;
	k[3][6]=20;
	k[4][1]=50;
	k[4][6]=30;
	k[5][2]=10;
	k[5][3]=40;
	k[6][0]=20;
	start.i=s;
	start.cweight=0;
	pq.push(start);
	while(!pq.empty())
	{
		current=pq.top();
		pq.pop();
		if(past[current.i]>current.cweight||flag[current.i]==-1)
		{
			past[current.i]=current.cweight;
			flag[current.i]=1;
		}
		for(j=0;j<n;j++)
		{
			if(k[current.i][j]!=-1)
				{
					next.i=j;
					next.cweight=current.cweight+k[current.i][j];
					if(past[next.i]>=next.cweight||flag[next.i]==-1)
						pq.push(next);
				}
		}
		cout<<"Success";
	}
present=e;
l=past[e];
cout<<'\n'<<"Backtrace End("<<e<<") <- ";
	while(present!=s)
	{
		for(j=0;j<n;j++)
			if(k[j][present]!=-1 && past[present]-k[j][present]==past[j])
			{
				present=j;
				cout<<j<<" <- ";
			}
	}
	cout<<'\n';
	return 0;
}