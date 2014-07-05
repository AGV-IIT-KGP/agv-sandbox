#include <stdio.h>
#include <iostream>
#include <math.h>
#include "Distance.h"
#include "Board.h"
using namespace std;

class Player
{
	private:
		int x,y,score;
	public:
		void newStatus(int , Circle*,return_data );
		void updtPos(int , Circle*, int );	
};
