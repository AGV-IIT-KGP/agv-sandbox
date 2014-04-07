#include <iostream>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <cstdlib>
//#include "findCentroid.cpp"
//#include "blobDetect.cpp"
//#include "Oops_class.h"

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
    void enqueue(int, int);
    void queueFront(int*, int*);
    void dequeue();

};

class image
    {   int score1;
        int score2;
        pos currentpos1;
        pos currentpos2;

    public:
        int count;
        cv::Mat img;
        cv::Mat img_bin;
        int **visited;
        image();
        pos *centroid;
        int bfs();
        int updatepos1();
        int updatepos2();
        void findCentroid();
        void printScore();
    };

image::image()
    {    
        score1=0,score2=0;
        count=0;
        score1=0;
        score2=0;
        

    }   
int image::bfs()
{   
    queue q;
    int x=0,y=0;
    int cols=img_bin.cols, rows=img_bin.rows;
    int count=1;
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
                    {   
                        q.queueFront(&y,&x);
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
    
    return count;
    
}

void image::findCentroid()
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
 

float calcDist(pos a, pos b)  //Calculating only the square of the distance
{
    float dist=0;
    dist= (a.x- b.x)*(a.x- b.x) + (a.y- b.y)*(a.y- b.y);
    return dist;
}
int image::updatepos1()
{   
    float temp=0;
    float minDist=2*(img.rows)*(img.cols)*(img.rows)*(img.cols);
    pos nearestC;
    int dice1=0;
    std::cout<<"Enter throw "<<std::endl;
    std::cin>>dice1;
    std::cout<<"Player 1's throw is "<<dice1<<std::endl;
    if(dice1%2==0)
        for(int i=0;i<count;i++)
        {
            if((centroid[i]).colour==0)
            {
                temp= calcDist(currentpos1,centroid[i]);
                if(temp<minDist)
                {
                    minDist=temp;
                    nearestC=centroid[i];
                }
                currentpos1=nearestC;
                score1+= 2*dice1;
            }
        }
    else if(dice1==1)
    {
        for(int i=0;i<count;i++)
        {
            if((centroid[i]).colour==2)
            {
                temp=calcDist(currentpos1,centroid[i]);
                if(temp<minDist)
                {
                    minDist=temp;
                    nearestC=centroid[i];
                }
                currentpos1=nearestC;
                score1+=10;
            }
        }
    }

    else 
    {
        for(int i=0;i<count;i++)
        {
            if((centroid[i]).colour==1)
            {
                temp=calcDist(currentpos1,centroid[i]);
                if(temp<minDist)
                {
                    minDist=temp;
                    nearestC=centroid[i];
                }
                currentpos1=nearestC;
                score1+=dice1;;
            }
        }
    }
    

    if(currentpos1.x==nearestC.x && currentpos1.y==nearestC.y)
        return 0;
    std::cout<<"New position of player 1 is "<<"("<<currentpos1.x<<","<<currentpos1.y<<")";     
    return 1;

}

int image::updatepos2()
{
    float temp=0;
    float minDist=2*(img.rows)*(img.cols)*(img.rows)*(img.cols);
    pos nearestC;
    int dice2=0;
    std::cout<<"Enter throw "<<std::endl;
    std::cin>>dice2;
    std::cout<<"Player 2's throw is "<<dice2<<std::endl;
    if(dice2%2==0)
        for(int i=0;i<count;i++)
        {
            if((centroid[i]).colour==0)
            {
                temp= calcDist(currentpos2,centroid[i]);
                if(temp<minDist)
                {
                    minDist=temp;
                    nearestC=centroid[i];
                }
            }
            currentpos2=nearestC;
            score2 += 2*dice2;
        }
    else if(dice2==1)
    {
        for(int i=0;i<count;i++)
        {
            if((centroid[i]).colour==2)
            {
                temp=calcDist(currentpos2,centroid[i]);
                if(temp<minDist)
                {
                    minDist=temp;
                    nearestC=centroid[i];
                }
                currentpos2=nearestC;
                score2+=10;
            }
        }
    }

    else 
    {
        for(int i=0;i<count;i++)
        {
            if((centroid[i]).colour==1)
            {
                temp=calcDist(currentpos2,centroid[i]);
                if(temp<minDist)
                {
                    minDist=temp;
                    nearestC=centroid[i];
                }
                currentpos2=nearestC;
                score2+=dice2;;
            }
        }
    }
    

    if(currentpos2.x==nearestC.x && currentpos2.y==nearestC.y)
        return 0;
    std::cout<<"New position of player 2 is "<<"("<<currentpos2.x<<","<<currentpos2.y<<")"<<std::endl;
    return 1;
}

void image::printScore()
{
    std::cout<<"Player 1's score= "<<score1<<std::endl;
    std::cout<<"Player 2's score= "<<score2<<std::endl;
}

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

cv::Mat binary(cv::Mat img,float threshold)
{   cv::Mat img_bin;
    //img=cv::imread("/home/aries/Desktop/1.jpg",0);
   // cvtColor(img,img_gray,CV_RGB2GRAY);
    cv::threshold(img,img_bin,threshold,255.0,cv::THRESH_BINARY);  
    cv::imwrite("img_bin3.jpg",img_bin);
    return img_bin;
}



int main()
{   
    std::cout<<"Welcome!!"<<std::endl;
    image img_class;
    img_class.img = cv::imread("/home/aries/Desktop/images.jpg",1);
    cv::imshow("img",img_class.img);
    cv::waitKey(0);
    img_class.img_bin= cv::imread("/home/aries/Desktop/images.jpg",0);
    cv::waitKey(0);
    //std::cout<<"Reading done"<<std::endl;
    int rows=img_class.img.rows;
    int cols=(img_class.img).cols;
    img_class.visited= new int*[rows];
    for(int j=0;j<rows;j++)
      img_class.visited[j]= new int[cols];
    for(int j=0;j<rows;j++)
     for(int i=0;i<cols;i++)
          img_class.visited[j][i]=-1;
    int flag1=1, flag2=1;
    int count=0;
    img_class.img_bin=binary(img_class.img_bin,10.0);
    cv::imshow("images",img_class.img_bin);
    cv::waitKey(0);
    img_class.count= img_class.bfs();
    count= img_class.count;
    img_class.centroid= new pos[img_class.count];
    for(int i=0;i<count;i++)
    {
        img_class.centroid[i].x=0;
        img_class.centroid[i].y=0;
    }
    img_class.findCentroid();
    while (flag1==1 && flag2==1)
    {
    	flag1=img_class.updatepos1();
    	flag2= img_class.updatepos2();
    	img_class.printScore();
    }

    std::cout<<"GAME OVER"<<std::endl;
    return 0;
}