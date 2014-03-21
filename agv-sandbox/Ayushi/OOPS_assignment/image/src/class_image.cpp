#include <image/class_image.h>

Image::Image()
{
cv::Mat image= cv::imread("image.jpg");

 visited = new int*[HEIGHT]; 
    for(int i=0;i<HEIGHT;i++) 
        visited[i]= new int[WIDTH]; 
    centroids= new Node[100];


}


int Image::isEmpty(){ 
    if(front==NULL) 
        return 1; 
    else return 0; 
} 
void Image::enqueue(int x,int y){ 
    Node* t = new Node();
    // create constructor  
    t->x=x; 
    t->y=y; 
    t->next=NULL; 
    if(isEmpty()){ 
        front=t; 
        rear=front; 
    } 
    else{ 
            rear->next=t; 
            rear=t; 
            rear->next=NULL; 
    } 
} 
void Image::queuefront(int *x,int *y){ 
    *x=front->x; 
    *y=front->y; 
    return; 
} 
void Image::dequeue(){ 
    Node* t; 
    if(isEmpty()){ 
        printf("Queue Underflow\n"); 
        return; 
    } 
    t=front; 
    front=t->next; 
    free(t); 
}

void Image::blobDetection(){ 
    int i,j,k,l,x,y; 
    no_of_centroids=0; 
	int blobsize=500;
    int height = HEIGHT; 
    int width = WIDTH; 
    //int **visited; 
   
    for(i=0; i < height;i++) 
        for(j=0;j < width;j++) 
            visited[i][j]=-1; 
      
    for(i=1;i<HEIGHT-1;i++){ 
        for(j=1;j<WIDTH-1;j++){ 
            if(image.at<cv::Vec3b>(i,j)[0]==255){    
                if(visited[i][j]==-1)
                { 
					
                    no_of_centroids++;
					
					}
					
					
                    front=NULL; 
                    enqueue(i,j); 
                    queuefront(&x,&y); 
                    while(!isEmpty()){ 
                        queuefront(&x,&y); 
                        dequeue(); 
  
                        for(k=x-1;k<=x+1;k++) 
                            for(l=y-1;l<=y+1;l++){ 
								if((k>0)&&(k<HEIGHT)&&(l>0)&&(l<WIDTH))
								 if(image.at<cv::Vec3b>(i,j)[0]==255 && visited[k][l]==-1){ 
                                        enqueue(k,l); 
                                        visited[k][l]=no_of_centroids; 
										blobsize++;
                                    } 
								 } 
                        visited[x][y]=no_of_centroids; 
						} 
  
					}   
				} 
			}

			//centroids=(Node*)malloc(sizeof(Node));

			for(int i=1;i<no_of_centroids;i++)
				centroids[i-1]=findCentroid(i);


        return; 
}


Node Image::findCentroid(int blobno)
	{
		int tx,ty,n;
		float cx,cy;
		Node centroid;
		centroid.next=NULL;
		int i,j;


		for(i=0;i<HEIGHT;i++)
			for(j=0;j<WIDTH;j++)
				if(visited[i][j]==blobno)
				{
					tx+=i;
					ty+=j;
					n++;
					
				}
		centroid.x=tx/n;
		centroid.y=ty/n;
		return centroid;
	}


	Node* Image::getCentroidList()
	{
		return centroids;
	}

