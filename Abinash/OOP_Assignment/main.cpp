#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Position.h"
#include "Board.h"
#include "Player.h"
#include "Image.h"
#include "Dice.h"
#include "Game.h"
#include "Dice6.h"

using namespace std;

int main()
{
   int b;
   srand((unsigned int)time(NULL));
   Game bgame;
   bgame.get_players();
   bgame.StartGame();
   cout<<"Winners :"<<endl;
   for (b=0;b<bgame.no_winners;b++)
   {
      cout<<"Player_"<<bgame.winset[b]->id<<endl;
   }
   return 0;
}
