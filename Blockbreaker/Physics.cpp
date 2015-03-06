#include "Physics.h"
#include "Entity.h"


Physic::Physic(Entity* entity)
{
   ballWidth = entity.getW();
   ballHeight = entity.getH();
}

void changeXDirection(double* x)
{
   *x = -1 * (*x);
}

void changeYDirection(double* y)
{
   *y = -1 * (*y);
}

//pass in the width of the object, height of object, its upper left hands coordinates, and the next position of the ball
bool Physic::checkForCollision(std::vector<Entity*> entities, int nextX, int nextY)
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
            for (int z = 0; z < entities.size(); z++)
               //increment through all the blocks
            {
               if (j >= entities[z]->getX() && j <= entities[z]->getX() + entities[z]->getW())
                  //if x coordinate of point between a blocks left x and right x
               {
                  if (nextY >= entities[z]->getY() && nextY <= entities[z]->getY() + entities[z]->getH())
                     //if y coordinate of point between blocks top y and bottom y
                  {
                     return true; //there is an intersection
                  }
               }
            }

         }
      }

      else //if not at top edge or bottom edge
      {
         for (int z = 0; z < entities.size(); z++)
            //go through vector of entities
         {

            //same logic as beforehand just in differen scenario
            if (x >= entities[z]->getX() && x <= entities[z]->getX() + entities[z]->getW())
            {
               if (nextY >= entities[z]->getY() && nextY <= entities[z]->getY() + entities[z]->getH())
               {
                  return true;
               }
            }

            else if (x + ballWidth >= entities[z]->getX() && x + ballWidth <= entities[z]->getX() + entities[z]->getWidth())
               //if right edge between entities x and y
            {
               if (nextY >= entities[z]->getY() && nextY <= entities[z]->getY() + entities[z]->getHeight())
               {
                  return true;
               }
            }
         }

         nextY += 1;
      }

   }

   return false;

}