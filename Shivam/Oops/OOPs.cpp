#include <iostream>
#include <cv_bridge.h>
#include <opencv2>

struct pos
    {
        int x;
        int y;
        int colour;
    };


struct node 
{ 
    int x; 
    int y; 
    struct node *next; 
};


class image
    {   int score1=0;
        int score2=0;
        img* a;
        int** visited;
        pos* c;

    public:
        pos current_pos1;
        pos current_pos2; 
        pos findcentroid(img* a,int blobno,int** visited);
        pos newposition(img*a);


	};

	 pos image::findcentroid(img *img,int blobno,int **visited)
	 {

		int tx=0,ty=0,n=0;
		float cx,cy;
		pos c;
		int i,j;
		for(i=0;i<img->height;i++)
			for(j=0;j<img->width;j++)
				if(visited[i][j]==blobno)
				{
					tx+=i;
					ty+=j;
					n++;					
				}

		c.x=tx/n;
		c.y=ty/n;
		return c;
	}

int** visitedlist(img* a,int *count)
{ 
    int i,j,k,l,x,y; 
    *count=0; 
	int blobsize=500;
    int height = a->height; 
    int width = a->width; 
    int **visited; 
    int** visited =new int*;
    for(i=0;i<a->height;i++) 
    int visited[i]=new int; 
    for(i=0;i<a->height;i++) 
        for(j=0;j<a->width;j++) 
            visited[i][j]=-1; 
      
    for(i=1;i<a->height-1;i++) 
        for(j=1;j<a->width-1;j++){ 
            if(colour(a,i,j,0)==255)
            {    
                if(visited[i][j]==-1)
                {

                   front=NULL; 
                    enqueue(i,j); 
                    queuefront(&x,&y); 
                    while(!isEmpty())
                    { 
                        queuefront(&x,&y); 
                        dequeue();
                    }
  
                    for(k=x-1;k<=x+1;k++) 
                        for(l=y-1;l<=y+1;l++)
                         	{ 
								if((k>0)&&(k<a->height)&&(l>0)&&(l<a->width))
								if(colour(a,k,l,0)==255 && visited[k][l]==-1){ 
                                        enqueue(k,l); 
                                        visited[k][l]=*count; 
										blobsize++;
                                    } 
								 } 
                        visited[x][y]=*count; 
						} 
  
					}   
				} 
			} 
        return visited; 
}


 
node *rear,*front;
 
int isEmpty()
{ 
    if(front==NULL) 
        return 1; 
    else return 0; 
} 

void enqueue(int x,int y)
{ 
    node* t; 
    node* t=new node;
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
void queuefront(int *x,int *y)
{ 
    *x=front->x; 
    *y=front->y; 
    return; 
} 
void dequeue()
{ 
    node* t; 
    if(isEmpty()){ 
        cout<<"Queue Underflow"<endl; 
        return; 
    } 
    t=front; 
    front=t->next; 
    delete t; 
}


int main()
{
	image i;
	return 0;
}