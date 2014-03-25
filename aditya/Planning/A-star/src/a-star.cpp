#include <stdio.h>
#include <set>
#include <vector>
#include <cmath>
using namespace std;
 
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
 
const int MAX = 1001;
const int MAXINT = 1000000000;
 
int n;
vvii G(MAX);	//adjacency list+cost
vi D(MAX, MAXINT);	//stores distn
vii POS(MAX);
 
int eucld(ii src, ii destn)
{
	return sqrt((src.first-destn.first)*(src.first-destn.first)+(src.second-destn.second)*(src.second-destn.second));
}

void ASTAR(int s)
{
    set<ii> Q;	//create queue
    D[s] = 0;	//get source distn zero
    Q.insert(ii(0,s));	//insert into queue
 
    while(!Q.empty())
    {
        ii top = *Q.begin();	
        Q.erase(Q.begin());		//pop
        int v = top.second;		
        int d = top.first;
 
        for (vii::const_iterator it = G[v].begin(); it != G[v].end(); it++)
        {
            int v2 = it->first;
            int cost = it->second;
            int heuristic=eucld(POS[v],POS[v2]);
            if (D[v2] > D[v] + cost + heuristic) 
            {
                if (D[v2] != 1000000000)
                {
                    Q.erase(Q.find(ii(D[v2], v2)));
                }
                D[v2] = D[v] + cost;
                Q.insert(ii(D[v2], v2));
            }
        }
    }
}
 
int main()
{
    int m, s, t = 0;
    printf("Enter number of vertex, edges, source and destination\n");
    scanf("%d %d %d %d", &n, &m, &s, &t);
    printf("\nEnter the x and y coordinate of each vertex:\n");
    for (int i = 0; i < n; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y );
        POS.push_back(ii(x, y));
    }
 	printf("\nEnter vertex of the edges and its cost:");
    for (int i = 0; i < m; i++)
    {
        int a, b, w = 0;
        scanf("%d %d %d", &a, &b, &w);
        G[a - 1].push_back(ii(b - 1, w));
        G[b - 1].push_back(ii(a - 1, w));
    }
 
    ASTAR(s - 1);
 
    printf("%d\n", D[t - 1]);
 
    return 0;
}