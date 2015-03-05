#include <SDL.h>
#include "Entity.h"
#include <vector>

class Physic
{  
   
   public:
      Physic(Entity ball);
      bool checkForCollision(std::vector<Entity> blocks, int nextX, int nextY);
      void changeXDirection(double* x);
      void changeYDirection(double* y);
      void changeXSpeed(double* x);
      void changeYSpeed(double* y);

   private:
      int ballWidth;
      int ballHeight;
};