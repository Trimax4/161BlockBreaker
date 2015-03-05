#include "Physics.h"
#include "Entity.h"


Physic::Physic(int ballWidth, int ballHeight)
{
   ballWidth = ballWidth;
   ballHeight = ballHeight;
}

void changeXDirection(double* x)
{
   *x = -1 * (*x);
}

void changeYDirection(double* y)
{
   *y = -1 * (*y);
}

bool Physic::checkForCollision(int objectWidth, int objectHeight, int objectX, int objectY, int nextX, int nextY)
{

   int x = nextX;

   for (int i = 0; i < ballHeight; i++)
   {

      x = nextX;

      if (i == 0 || i == ballHeight - 1)
      {
         for (int j = nextX; j <= nextX + ballWidth; j++)
         {

            if (j >= objectX && j <= objectX + objectWidth)
            {
               if (nextY >= objectY && nextY <= objectY + objectHeight)
               {
                  return true;
               }
            }


         }
      }


      else
      {


         if (x >= objectX && x <= objectX + objectWidth)
         {
            if (nextY >= objectY && nextY <= objectY + objectHeight)
            {
               return true;
            }
         }

         else if (x + ballWidth >= objectX && x + ballWidth <= objectX + objectWidth)
         {
            if (nextY >= objectY && nextY <= objectY + objectHeight)
            {
               return true;
            }
         }
      }

      nextY += 1;


   }



   return false;

}