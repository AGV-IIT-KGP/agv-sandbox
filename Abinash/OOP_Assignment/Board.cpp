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
   int i,j,k;
   x=&A;
   x->rn=99;
   x->gn=99;
   x->bn=99;//Board::mapped(img,&height,&width,&A);
   for (i=0;i<99;i++)
   {
      x->r[i].x=rand()%640;
      x->g[i].x=rand()%640;
      x->b[i].x=rand()%640;
      x->r[i].y=-(rand()%480);
      x->g[i].y=-(rand()%480);
      x->b[i].y=-(rand()%480);
   }
}
