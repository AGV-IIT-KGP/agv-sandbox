#include<iostream>
#include<cstdio>
#include "point.h"
#include "image.h"
using namespace std;

class evt: public pt{
public:
evt(int a,int b): pt(a,b){};	
int score,dice,can_play;
void score_update(image img);
int detect_circle(image img);
};
