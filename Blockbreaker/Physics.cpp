#include "Physics.h"
#include "Entity.h"
#include <cmath>

#define PI 3.14159265

namespace
{
   double distance(int x1, int y1, int x2, int y2)
   {
      return std::sqrt(std::pow((double)x2 - (double)x1, 2) + std::pow((double)y2 - (double)y1, 2));
   }

}

Physic::Physic(Entity* entity)
{
   ballWidth = entity->getW();
   ballHeight = entity->getH();
   ball = entity;
}

void changeXDirection(double* x)
{
   *x = -1 * (*x);
}

void changeYDirection(double* y)
{
   *y = -1 * (*y);
}

//USED FOR RECTANGLE COLLISION, NOT RELEVANT TO OUR DEMOpass in the width of the object,, height of object, its upper left hands coordinates, and the next position of the ball
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
            if (entities[z] == ball)
            {
               continue;
            }
            //same logic as beforehand just in differen scenario
            if (x >= entities[z]->getX() && x <= entities[z]->getX() + entities[z]->getW())
            {
               if (nextY >= entities[z]->getY() && nextY <= entities[z]->getY() + entities[z]->getH())
               {
                  return true;
               }
            }

            else if (x + ballWidth >= entities[z]->getX() && x + ballWidth <= entities[z]->getX() + entities[z]->getW())
               //if right edge between entities x and y
            {
               if (nextY >= entities[z]->getY() && nextY <= entities[z]->getY() + entities[z]->getH())
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

bool Physic::checkForCircleCollision(std::vector<Entity*> entities, int nextX, int nextY)
{
   int xCenter = (nextX + ballWidth / 2); //get the x value of center of circle
   int yCenter = (nextY + ballHeight / 2); //get the y value of the center of circle
   int closestX;
   int closestY;
   for (int i = 0; i < entities.size(); i++)
   {
      if (entities[i] == ball)
      {
         continue;
      }
      if (xCenter < entities[i]->getX())
      {
         closestX = entities[i]->getX();
      }
      else if (xCenter > entities[i]->getX() + entities[i]->getW())
      {
         closestX = entities[i]->getX() + entities[i]->getW();
      }
      else
      {
         closestX = xCenter;
      }

      if (yCenter < entities[i]->getY())
      {
         closestY = entities[i]->getY();
      }
      else if (yCenter > entities[i]->getY() + entities[i]->getH())
      {
         closestY = entities[i]->getY() + entities[i]->getH();

      }
      else
      {
         closestY = yCenter;
      }

      if (distance(xCenter, yCenter, closestX, closestY) < (ballWidth / 2))
      {
         return true;
      }
   }

   return false;
}


// use 0 to 180 for top two quadrants, -0 to -180 for bottom two quadrants, pass in new angle and velocity in x and y direction
void Physic::changeDirection(double angle, double* x, double *y)
{  
   
   double xSpeed = *x;
   double ySpeed = *y;
   double radians = angle * (PI / 180);

   if (angle == 90)
   {
      *x = 0;
      *y = std::sin(PI - radians) * (std::sqrt(xSpeed * xSpeed + ySpeed * ySpeed));
   }
   else if (angle == -90)
   {
      *x = 0;
      *y = std::sin(radians) * (std::sqrt(xSpeed * xSpeed + ySpeed * ySpeed));
   }
   else if (angle == 0)
   {
      *x = std::sqrt(xSpeed * xSpeed + ySpeed * ySpeed);
      *y = 0;
   }
   else if (angle == 180 || angle == -180)
   {
      *x = -std::sqrt(xSpeed * xSpeed + ySpeed * ySpeed);
      *y = 0;
   }
   else if (x >= 0 && angle <= 180)
   {
      *x = -std::cos(PI - radians) * (std::sqrt(xSpeed * xSpeed + ySpeed * ySpeed));
      *y = std::sin(PI - radians) * (std::sqrt(xSpeed * xSpeed + ySpeed * ySpeed));
   }
   else if (angle >= -90 && x < 0)
   {
      *x = std::cos(radians) * (std::sqrt(xSpeed * xSpeed + ySpeed * ySpeed));
      *y = std::sin(radians) * (std::sqrt(xSpeed * xSpeed + ySpeed * ySpeed));
   }
   else
   {
      *x = std::cos(PI - std::abs(radians)) * (std::sqrt(xSpeed * xSpeed + ySpeed * ySpeed));
      *y = std::cos(PI - std::abs(radians)) * (std::sqrt(xSpeed * xSpeed + ySpeed * ySpeed));
   }
   
}

//xSpeed = 5 ySpeed = -4
//radians = -90 * PI/180 = -PI/2
//*x = 

void Physic::changeSpeed(double newSpeed, double* x, double* y)
{  
   double xSpeed = *x;
   double ySpeed = *y;

   double angle = std::atan(ySpeed / xSpeed);
   angle = std::abs(angle);

   if (xSpeed == 0 && ySpeed != 0)
   {
      if (ySpeed < 0)
      {
         *y = -newSpeed;
      }
      else
      {
         *y = newSpeed;
      }
   }
   else if (xSpeed != 0 && ySpeed == 0)
   {
      if (xSpeed < 0)
      {
         *x = -newSpeed;
      }
      else
      {
         *x = newSpeed;
      }
   }
   else if (xSpeed < 0 && ySpeed < 0)
   {
      *x = -std::cos(angle) * newSpeed;
      *y = -std::sin(angle) * newSpeed;
   }
   else if (xSpeed > 0 && ySpeed < 0)
   {
      *x = std::cos(angle) * newSpeed;
      *y = -std::sin(angle) * newSpeed;
   }
   else if (xSpeed < 0 && ySpeed > 0)
   {
      *x = -std::cos(angle) * newSpeed;
      *y = std::sin(angle) * newSpeed;
   }
   else
   {
      *x = std::cos(angle) * newSpeed;
      *y = std::sin(angle) * newSpeed;
   }
}


