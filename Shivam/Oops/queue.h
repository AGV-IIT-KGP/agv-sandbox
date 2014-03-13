#include <iostream>
#include "node.h"

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
 
