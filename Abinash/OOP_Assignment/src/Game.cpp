#include "Game.h"
#include <conio.h>

void Game::get_players()
{
   int i;
   std::cout<<"Enter the number of players\n";
   std::cin>>no_players;
   Set=new Player [no_players];
   winset=new Player* [no_players];
   for (i=0;i<no_players;i++)
   {
      Set[i].id=i;
   }
}

void Game::trialturn()
{
   int i;
   for (i=0;i<no_players;i++)
   {
      getch();
      Set[i].Getdice(dice.roll(),&bd1);
      std::cout<<"\tPlayer_"<<Set[i].id<<" @ "<<Set[i].pos.x<<","<<Set[i].pos.y<<" With score="<<Set[i].score<<"\n"<<std::endl;
   }
   return;
}

void Game::StartGame()
{
   int j,k,l;

   Player* tmpset=new Player [no_players];
   for (l=0;l<no_players;l++)
      {
         tmpset[l]=Set[l];
      }
   for (j=0;no_winners==0;j++)
   {
      std::cout<<"Round--"<<j+1<<std::endl;
      Game::trialturn();
      for (k=0;k<no_players;k++)
      {
         if (tmpset[k].pos.x==Set[k].pos.x && tmpset[k].pos.x==Set[k].pos.x)
         {

            winset[no_winners++]=&Set[k];

         }
      }
      for (l=0;l<no_players;l++)
      {
         tmpset[l]=Set[l];
      }
   }
   return;
}

Game::Game()
{
   no_winners=0;
}

