#include <SDL.h>
#include "Entity.h"
#include <vector>

class Physic
{  
   
   public:
      Physic(SDL_Rect ball);
      bool checkForCollision(std::vector<Entity> blocks, int nextX, int nextY);


   private:
      int ballWidth;
      int ballHeight;
};