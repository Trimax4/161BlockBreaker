#include <SDL.h>
#include "Entity.h"
#include <vector>

class Physic
{  
   
   public:
      Physic(Entity ball);
      bool checkForCollision(std::vector<Entity> blocks, int nextX, int nextY);


   private:
      int ballWidth;
      int ballHeight;
};