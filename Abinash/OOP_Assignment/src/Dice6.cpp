#include "Dice6.h"
#include <ctime>
#include <cstdlib>


int Dice6::roll()
{
   srand((unsigned int)time(NULL));
   return (rand()%6)+1;//ctor
}
