#include <SDL.h>
#include "Entity.h"
#include <vector>


class Physic
{

public:
	Physic(Entity* entity);
	bool checkForCollision(std::vector<Entity*> entities, int nextX, int nextY);
	bool checkForCircleCollision(std::vector<Entity*> entities, int nextX, int nextY);
	int getCircleCollision(std::vector<Entity*> entities, int nextX, int nextY);
	void changeXDirection(double* x);
	void changeYDirection(double* y);
	void changeXSpeed(double* x, double newSpeed);
	void changeYSpeed(double* y, double newSpeed);
	void changeDirection(double angle, double* x, double *y);
	void changeSpeed(double newSpeed, double* x, double* y);
	bool hitBrickBottom(int brickY, int ballY); // Added after 3-11
	bool hitBrickTop(int brickY, int ballY); // Added after 3-11

private:
	int ballWidth;
	int ballHeight;
	Entity* ball;
};