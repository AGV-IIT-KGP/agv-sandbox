#include<iostream>
#include<cstdio>
using namespace std;

class image{
public:int height,width,channels;
int **r_pixel,**g_pixel,**b_pixel;
public: image(int x,int y,int c);

};
