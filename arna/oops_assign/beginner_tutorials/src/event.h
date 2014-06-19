#include<iostream>
#include<cstdio>
#include "point.h"
#include "image_proc101.cpp"

using namespace std;

class evt: public pt{
public:int score,dice,can_play;
evt(int a,int b): pt(a,b){
	score=0;can_play=0;
};	

void score_update(image* img);
int detect_circle(image* img);
};
