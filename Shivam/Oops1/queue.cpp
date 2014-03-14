#include <iostream>
#include "queue.h"

int queue::isEmpty()
{ 
    if(front==NULL) 
        return 1; 
    else return 0; 
} 

void queue::enqueue(int x,int y)
{ 
   
    node *t=new node;
    t->x=x; 
    t->y=y; 
    t->next=NULL; 
    if(isEmpty()){ 
        front=t; 
        rear=front; 
    } 
    else
    	{ 
            rear->next=t; 
            rear=t; 
            rear->next=NULL; 
   		} 
} 
void queue::queueFront(int *x, int *y)
{ 
    *x=front->x; 
    *y=front->y; 
    return; 
} 
void queue::dequeue()
{ 
    node *t; 
    if(isEmpty()){ 
        std::cout<<"Queue Underflow"<<std::endl; 
        return; 
    } 
    t=front; 
    front=t->next; 
    delete t; 
}
