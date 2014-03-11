#include <iostream>

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