#include <SDL.h>
#include "Entity.h"
#include <vector>

class Physic
{  
   
   public:
      Physic(int ballWidth, int ballHeight);
      bool checkForCollision(int objectWidth, int objectHeight, int objectX, int objectY, int nextX, int nextY);
      void changeXDirection(double* x);
      void changeYDirection(double* y);
      void changeXSpeed(double* x, double newSpeed);
      void changeYSpeed(double* y, double newSpeed);

   private:
      int ballWidth;
      int ballHeight;
};