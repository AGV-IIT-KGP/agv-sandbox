#include "Player.h"

void Player::upgrade_score(int* x,int y)
{
   switch (y){
   case 1:
      *x+=10;
      break;
   case 2:
   case 4:
   case 6:
      (*x)+=y*2;
      break;
   default:
      *x+=y;
      break;
   }
   return;
}

void Player::shift_position(Position *x,int y,Board *bd)
{
   int i,j,k,flag=-1;
   float minim,dist;

   switch (y){
   case 1:
      {
      for (i=0,flag=-1;i<(bd->A.bn);i++)
      {

         if (((bd->A).b[i].x)>(x->x) && ((bd->A).b[i].y)<(x->y))
         {
            dist=((bd->A.b[i].x)-(x->x))*((bd->A.b[i].x)-(x->x))+((bd->A.b[i].y)-(x->y))*((bd->A.b[i].y)-(x->y));
            dist=sqrt(dist);
            if (i==0)minim=dist;
            if (dist<minim){
               minim=dist;
               flag=i;
            }
         }
      }

      if(flag!=-1){(x->x)=(bd->A).b[flag].x;(x->y)=(bd->A).b[flag].y;}

      }
      break;
   case 2:
   case 4:
   case 6:
      {
      for (j=0,flag=-1;j<(bd->A.rn);j++)
      {

         if (((bd->A).r[j].x)>(x->x) && ((bd->A).r[j].y)<(x->y))
         {
            dist=((bd->A.r[j].x)-(x->x))*((bd->A.r[j].x)-(x->x))+((bd->A.r[j].y)-(x->y))*((bd->A.r[j].y)-(x->y));
            dist=sqrt(dist);
            if (j==0)minim=dist;
            if (dist<minim){
               minim=dist;
               flag=j;
            }
         }
      }

      if(flag!=-1){(x->x)=(bd->A).r[flag].x;(x->y)=(bd->A).r[flag].y;}

      }
      break;
   default:
      {
      for (k=0,flag=-1;k<(bd->A.gn);k++)
      {

         if (((bd->A).g[k].x)>(x->x) && ((bd->A).g[k].y)<(x->y))
         {
            dist=((bd->A.g[k].x)-(x->x))*((bd->A.g[k].x)-(x->x))+((bd->A.g[k].y)-(x->y))*((bd->A.g[k].y)-(x->y));
            dist=sqrt(dist);
            if (k==0)minim=dist;
            if (dist<minim){
               minim=dist;
               flag=k;
            }
         }
      }

      if(flag!=-1){(x->x)=(bd->A).g[flag].x;(x->y)=(bd->A).g[flag].y;}

   }
      break;
   }
   return;
}

void Player::Getdice(int dice,Board *bd)
{

   upgrade_score(&score,dice);
   //std::cout<<"P2";
   shift_position(&pos,dice,bd);
   switch (dice){
   case 1:
      std::cout <<"\tPlayer_"<<this->id<<" Gets a "<<dice<<" Moves to Blue Circle"<<std::endl;
      break;
   case 2:
   case 4:
   case 6:
      std::cout <<"\tPlayer_"<<this->id<<" Gets a "<<dice<<" Moves to Red Circle"<<std::endl;
      break;
   default:
      std::cout <<"\tPlayer_"<<this->id<<" Gets a "<<dice<<" Moves to Green Circle"<<std::endl;
      break;
   }
}

Player::Player()
{
   score=0;
}
