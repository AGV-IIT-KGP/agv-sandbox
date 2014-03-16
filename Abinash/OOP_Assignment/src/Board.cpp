#include "Board.h"
#include <cstdlib>
#include <ctime>

//void Board::mapped(Image img,int *x,int *y,chan *pa)
//{


//}

Board::Board()
{
   srand((unsigned int)time(NULL));
   Chan *x;
   x=&A;
   x->rn=0;
   x->gn=0;
   x->bn=0;//Board::mapped(img,&height,&width,&A);
}
