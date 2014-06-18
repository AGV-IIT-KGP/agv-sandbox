#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
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
   srand((unsigned int)time(NULL));
   Game bgame;
   cout<<"s"<<endl;
   Image bimg("fgame.bmp",&(bgame.bd1));
   for (int i=0;i<(bgame.bd1.A.rn);i++)
   {
      cout<<bgame.bd1.A.r[i].x<<" "<<bgame.bd1.A.r[i].y<<endl;
   }
   bgame.get_players();
   bgame.StartGame();
   cout<<"Winners :"<<endl;
   for (int b=0;b<bgame.no_winners;b++)
   {
      cout<<"Player_"<<bgame.winset[b]->id<<endl;
   }
   return 0;
}
