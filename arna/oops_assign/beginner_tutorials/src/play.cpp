#include<iostream>
#include "game.cpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
using namespace std;

pt:: pt(int a,int b){
x=a;
y=b;
}


image:: image(int x,int y,int z): height(x),width(y),channels(z){int i;
r_pixel=(int**)malloc(x*sizeof(int*));
for(i=0;i<x;i++)r_pixel[i]=(int*)malloc(y*sizeof(int));
g_pixel=(int**)malloc(x*sizeof(int*));
for(i=0;i<x;i++)g_pixel[i]=(int*)malloc(y*sizeof(int));
b_pixel=(int**)malloc(x*sizeof(int*));
for(i=0;i<x;i++)b_pixel[i]=(int*)malloc(y*sizeof(int));
}

int evt:: detect_circle(image img){int i,j;
	if(i>=img.height || j>=img.width)return 0;
if(dice%2==0){
for(i=x;i<img.height;i++){
	for( j=y+1;j<img.width;j++){
		if(img.r_pixel[i][j]==255){can_play=1;break;}
		else can_play=0;}}
}
else if(dice==1){
for( i=x;i<img.height;i++){
	for( j=y+1;j<img.width;j++){
		if(img.b_pixel[i][j]==255){can_play=1;break;}
		else can_play=0;}}
}
else {
for( i=x;i<img.height;i++){
	for( j=y+1;j<img.width;j++){
		if(img.g_pixel[i][j]==255){can_play=1;break;}
		else can_play=0;}}
}
if(can_play){
x=i;y=j;}
cout<<"x="<<x<<" ,y="<<y<<endl;
return can_play;
}


void evt::score_update(image img){
if(dice%2==0 && detect_circle(img))score+=2*dice;
else if(dice==1){score+=10;int x=detect_circle(img);}
else {score+=dice;int x=detect_circle(img);}
return;
}


int main(){
int n;
cout<<"input no. of players: ";
cin>>n;
image* img=new image(2,2,3);
img->r_pixel[0][0]=255;img->g_pixel[0][0]=0;img->b_pixel[0][0]=0;
img->r_pixel[0][1]=255;img->g_pixel[0][1]=0;img->b_pixel[0][1]=0;
img->r_pixel[1][0]=255;img->g_pixel[1][0]=0;img->b_pixel[1][0]=0;
img->r_pixel[1][1]=255;img->g_pixel[1][1]=0;img->b_pixel[1][1]=0;
while(n--){
game* G1=new game(0,0);
evt* E=new evt(0,0);
do{
cin>>E->dice;
E->score=G1->score;
E->x=G1->x;
E->y=G1->y;
E->score_update(*img);
G1->score=E->score;
}while(E->can_play);
cout<<"score= "<<G1->score<<endl;
}
return 0;}

