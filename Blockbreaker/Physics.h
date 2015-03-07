#include <SDL.h>
#include "Entity.h"
#include <vector>


class Physic
{  
   
   public:
      Physic(Entity* entity);
      bool checkForCollision(std::vector<Entity*> entities, int nextX, int nextY);
      bool checkForCircleCollision(std::vector<Entity*> entities, int nextX, int nextY);
      void changeXDirection(double* x);
      void changeYDirection(double* y);
      void changeXSpeed(double* x, double newSpeed);
      void changeYSpeed(double* y, double newSpeed);

   private:
      int ballWidth;
      int ballHeight;
      Entity* ball;
};