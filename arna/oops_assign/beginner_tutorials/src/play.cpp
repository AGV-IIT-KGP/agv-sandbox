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


int evt::detect_circle(image* real){int present;
	cout<<"starting pos="<<x<<","<<y<<endl;
	if(x>=real->img.rows || y>=real->img.cols)return 0;
int i;
if(dice%2==0){
		present=real->A[x][y];
for(i=present+1;i<=real->mark;i++){
	if(real->img.at<cv::Vec3b>(real->count_x[i],real->count_y[i])[2]==255){can_play=1;break;}
	else can_play=0;}}
else if(dice==1){
	present=real->A[x][y];
for(i=present+1;i<=real->mark;i++){
	if(real->img.at<cv::Vec3b>(real->count_x[i],real->count_y[i])[0]==255){can_play=1;break;}
	else can_play=0;}
}
else{
	present=real->A[x][y];
for(i=present+1;i<=real->mark;i++){
	if(real->img.at<cv::Vec3b>(real->count_x[i],real->count_y[i])[1]==255){can_play=1;break;}
	else can_play=0;}
}
if(i>real->mark)can_play=0;
if(can_play){
x=real->count_x[i];y=real->count_y[i];}
cout<<"present="<<present<<",x="<<x<<" ,y="<<y<<endl;
return can_play;
}

/*int evt:: detect_circle(image* img){int i,j;
	if(x>=img.rows || y>=imgcols)return 0;
if(dice%2==0){
for(i=x;i<img.rows;i++){
	for( j=y+1;j<img.cols;j++){
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
}*/


void evt::score_update(image* img){
if(dice%2==0 && detect_circle(img))score+=2*dice;
else if(dice==1){score+=10;int x=detect_circle(img);}
else {score+=dice;int x=detect_circle(img);}
return;
}


int main(){
int n;
image* real=new image(10);
real->process_image();
cout<<"input no. of players: ";
cin>>n;
int t=n; //total players
cout<<n<<" players are playing"<<endl;
game* G=new game(0,0);
while(n--){

evt* E=new evt(0,0);
do{
	cout<<"input dice outcome:"; 
cin>>E->dice;
cout<<"passing pos:-"<<E->x<<","<<E->y<<endl;
E->score_update(real);
cout<<"at position:-"<<E->x<<","<<E->y<<endl;
//G1->score=E->score;
//G1->x=E->x;G1->y=E->y;
}while(E->can_play);
cout<<"score= "<<E->score<<endl<<endl;
if(E->score>G->winner_score){
	G->winner_score=E->score;G->winner_id=t-n;  //if player 1 and 2 have same score, player 1 is winner, not 2 (assumed for simplicity).
}
}
cout<<"WINNER is player "<<G->winner_id<<" with score="<<G->winner_score<<endl;
return 0;}


