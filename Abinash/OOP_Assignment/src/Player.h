#ifndef PLAYER_H
#define PLAYER_H
#include "Position.h"
#include "Board.h"
#include <iostream>
#include <cmath>

class Player
{
   public:
      Position pos;
      int score,id;
      void Getdice(int,Board*);
      Player();
   private:
      void shift_position(Position*,int,Board*);
      void upgrade_score(int*,int);
};

#endif // PLAYER_H
