#ifndef queue_h
#define queue_h
#include <iostream>
#include "queue.cpp"

struct node 
{ public:
    int x; 
    int y; 
    node *next; 
};

class queue
{
	node *front, *rear;
public:
	queue(){front=NULL; 
		    rear=NULL;}
	int isEmpty();
	void enqueue(int x, int y);
	void queueFront(int *x, int *y);
	void dequeue();

};

#endif
 
