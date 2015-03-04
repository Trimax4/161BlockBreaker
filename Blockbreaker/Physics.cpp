#include "Physics.h"
#include "Entity.h"


Physic::Physic(SDL_Rect ball)
{
   ballWidth = ball.w;
   ballHeight = ball.h;
}
bool Physic::checkForCollision(std::vector<Entity> blocks, int nextX, int nextY)
{

   int x = nextX;

   for (int i = 0; i < ballHeight; i++)
      //from the top of the paddle to the bottom
   {
      x = nextX;

      if (i == 0 || i == ballHeight - 1)
         //if at top edge or bottom edge
      {
         for (int j = nextX; j <= nextX + ballWidth; j++)
            //from left edge to right edge
         {
            for (int z = 0; z < blocks.size(); z++)
               //increment through all the blocks
            {
               if (j >= blocks[z].getX() && j <= blocks[z].getX() + blocks[z].getWidth())
                  //if x coordinate of point between a blocks left x and right x
               {
                  if (nextY >= blocks[z].getY() && nextY <= blocks[z].getY() + blocks[z].getHeight())
                     //if y coordinate of point between blocks top y and bottom y
                  {
                     return true; //there is an intersection
                  }
               }
            }

         }
      }
      /*
      else //if not at top edge or bottom edge
      {
         for (int z = 0; z < blocks.size(); z++)
            //go through vector of entities
         {

            //same logic as beforehand just in differen scenario
            if (x >= blocks[z].getX() && x <= blocks[z].getX() + blocks[z].getWidth())
            {
               if (nextY >= blocks[z].getY() && nextY <= blocks[z].getY() + blocks[z].getHeight())
               {
                  return true;
               }
            }

            else if (x + ballWidth >= blocks[z].getX() && x + ballWidth <= blocks[z].getX() + blocks[z].getWidth())
               //if right edge between entities x and y
            {
               if (nextY >= blocks[z].getY() && nextY <= blocks[z].getY() + blocks[z].getHeight())
               {
                  return true;
               }
            }
         }
         
         nextY += 1;
      }
      */
   }
   
   return false;

}