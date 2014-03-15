#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Dice6.h"
#include "Board.h"
#include "Dice.h"


class Game
{
   public:
      void StartGame();
      void get_players ();//takes no of players and makes players with unique ids
      Player** winset;
      int no_winners;
      Game();
   private:

      int no_players;

      void trialturn();//executes one turn for each player
      Player *Set;
      Dice6 dice;
      Board bd1;
};

#endif // GAME_H
