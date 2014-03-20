#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <cstdlib>

class pos
    {
     public:
        pos()
        {
            x=0,y=0;colour=0;
        }
        int x;
        int y;
        int colour;
    };

class node 
{ 
public:
    int x; 
    int y; 
    node *next; 
};

class queue
{
    node *front, *rear;
public:
    queue()
    {
        front=NULL; 
        rear=NULL;
    }
    int isEmpty();
    void enqueue(int, int);
    void queueFront(int*, int*);
    void dequeue();

};

class img_process
{
public:
    cv::Mat img;
  //  node *lane1, *lane2;
    int **visited;
    pos *centroid;
    int count;
    cv::Mat binary(cv::Mat, float threshold);
    void bfs(cv::Mat img_bin);
    void findCentroid(cv::Mat img_bin);
    cv::Mat colour(cv::Mat, int, int);
    cv::Mat link(cv::Mat img_bin, int thresh);
   // img_process();

};

/*img_process::img_process()                       //Possible source of error
{
    lane1=NULL;
    lane2=NULL;
}*/

int queue::isEmpty()
{ 
    if(front==NULL) 
        return 1; 
    else return 0; 
} 

void queue::enqueue(int y, int x)
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
void queue::queueFront(int *y, int *x)
{ 
    *x=front->x; 
    *y=front->y; 
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

float dist_sq(pos a, pos b)
{
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

cv::Mat img_process::colour(cv::Mat img_bin,int val, int rgb)  //rgb= 1 or 2 depending on lane colour
{
    for(int i=0;i<img_bin.rows;i++)
        for(int j=0;j<img_bin.cols;j++)
            {
                if(visited[i][j]==val)
                {
                    cv::Vec3b point= img_bin.at<cv::Vec3b>(i,j);
                    point[rgb]= 255;
                }
            }
    return img_bin;
}

cv::Mat img_process::binary(cv::Mat img_gray,float threshold)
{   cv::Mat img_bin;
    cv::threshold(img_gray,img_bin,threshold,255,cv::THRESH_BINARY);  
    cv::imwrite("img_bin4.jpg",img_bin);
    return img_bin;
}

void img_process::bfs(cv::Mat img_bin)
{   
    int **visited=new int*[img_bin.rows];
    for(int i=0;i<img_bin.rows;i++)
        visited[i]=new int[img_bin.cols];
    for(int i=0;i<img_bin.rows;i++)
        for(int j=0;j<img_bin.cols;j++)
            visited[i][j]=-1;

    queue q;
    int x=0,y=0;
    int cols=img_bin.cols, rows=img_bin.rows;
    count=1;

    for(int j=0;j<img_bin.rows;j++)
        for(int i=0;i<img_bin.cols;i++)
        {
           if((img_bin.at<uchar>(j,i))==255)
           {
                if(visited[j][i]==-1)
                {
                    q.enqueue(j,i);
                    q.queueFront(&y,&x);
                    visited[j][i]=0;
                    while(!q.isEmpty())
                    {   q.queueFront(&y,&x);
                        q.dequeue();
                        for(int l=y-1;l<=y+1;l++)
                        for(int k=x-1;k<=x+1;k++)
                        {
                            if(k>0 && k<cols && l>0 && l<rows && visited[l][k]==-1 && img_bin.at<uchar>(l,k)==255)
                            {   
                                q.enqueue(l,k);
                                visited[l][k]=count;

                            }
                        }
                         visited[y][x]=count;
                    }
                    count++; 
                }
            }
        }
        cv::imshow("images",img_bin);
}

void img_process::findCentroid(cv::Mat img_bin)
{ 
    int *pixels= new int[count];
    int blobno=0;
    int rows=img_bin.rows;
    int cols=img_bin.cols;

    for(int j=0;j<rows;j++)
    {
        for(int i=0;i<cols;i++)
        {
           if(visited[j][i]!=-1)
           {
                blobno=visited[j][i];
                centroid[blobno].x +=i;
                centroid[blobno].y +=j;
                pixels[blobno]++;
            
           }
        }
    }
    for(int i=0;i<count;i++)
    {
        centroid[i].x/= pixels[i];
        centroid[i].y/=pixels[i];
    }   
    delete pixels;            

    pos centre;
    for(int i=0;i<count;i++)
    {
        centre=centroid[i];
        cv::Vec3b point= img.at<cv::Vec3b>(centre.x,centre.y);
        if(point[0]>1500 && point[1]<100 && point[2]<100)
            (centroid[i]).colour= 0;
        else if(point[0]<100 && point[1]>150 && point[2]<100)
            (centroid[i]).colour= 1;
        else if(point[0]<100 && point[1]<100 && point[2]>150)
            (centroid[i]).colour= 2;
    }                                                                           
}


cv::Mat img_process::link(cv::Mat img_bin,int thresh)
{
    float thresh_sq=thresh*thresh;
    int j=1, flag=0,val=0;
    float temp=0, temp_pos=0;
   // lane1.x= &(centroid[1]).x;
    //lane1.y= &(centroid[1]).y;
    for(int i=1;i<=count;i++)
    {   val= visited[centroid[i].y][centroid[i].x];
        
        img_bin=colour(img_bin, val,1);
        visited[(centroid[i]).y][(centroid[i]).x]=1;
        cv::namedWindow("image",CV_WINDOW_AUTOSIZE);
        cv::imshow("image",img_bin);
        cv::waitKey(0);
        j=i+1;
        while(!flag)
        {
            if (dist_sq(centroid[i], centroid[j]) < thresh_sq)
            {
              //  lane1=lane1->next;
              //  lane1.x= &(centroid[j].x);
              //  lane1.y= &(centroid[j].y);

                flag++;
                i=j;
            }
            else
                j++;
        }

    }
    
   // lane1->next=NULL;
    int i=1;
    flag=0;
    for(;!flag;i++)
    {
        if(visited[(centroid[i]).y][(centroid[i]).x]!=1)
            flag++;
    }
    i--;

  //  lane2.x= &centroid[i].x;
    //lane2.y= &centroid[i].y;
    for(;i<=count;i++)
    {   val= visited[(centroid[i]).y][(centroid[i]).x];
        img_bin=colour(img_bin, val,2);
        visited[(centroid[i]).y][(centroid[i]).x]=2;
        j=i+1;
    //  cv::namedWindow("image",CV_WINDOW_AUTOSIZE);
        cv::imshow("image",img_bin);
        cv::waitKey(0);
        
        while(!flag)
        {
            if (dist_sq(centroid[i], centroid[j]) < thresh_sq)
            {
              //  lane2=lane2->next;
               // lane2.x= centroid[j].x;
               // lane2.y= centroid[j].y;

                flag++;
                i=j;
            }
            else
                j++;
        }

    }
   // lane2->next=NULL;
    return img_bin;
}   

int main()
{
    cv::waitKey(0);
    img_process img_p;
    cv::Mat img,img_bin, img_lanes;
    img_p.img= cv::imread("/home/aries/Desktop/images.jpg",3);
    img_bin= cv::imread("/home/aries/Desktop/images.jpg",0);
    img_bin= img_p.binary(img_bin,10);
    cv::namedWindow("image",CV_WINDOW_AUTOSIZE);
    cv::imshow("image",img_bin);
    cv::waitKey(0);
    img_p.bfs(img_bin);
    img_p.centroid= new pos[img_p.count];
    for(int i=0;i<img_p.count;i++)
    {
        img_p.centroid[i].x=0;
        img_p.centroid[i].y=0;
    }
    cv::imshow("image",img);
    cv::waitKey(0);
    img_p.findCentroid(img_bin);
    img_lanes= img_p.link(img_bin,50);
    return 0;
}


