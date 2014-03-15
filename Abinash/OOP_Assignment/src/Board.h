#ifndef BOARD_H
#define BOARD_H
#include "Position.h"
#include "Image.h"

struct pix{
   char c;
   Position p;
};

struct Chan{
   Position r[100];int rn;
   Position g[100];int gn;
   Position b[100];int bn;
};

class Board
{
   public:
      int height,width;
      Chan A;
      Board();
   private:
      //void mapped(Image,int*,int*,chan *pa);

};

#endif // BOARD_H
