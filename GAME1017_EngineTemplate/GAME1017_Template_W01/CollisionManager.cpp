#include "CollisionManager.h"


bool CollisionManager::AABBCheck(const SDL_FRect& object1, const SDL_FRect& object2)
{
	SDL_Rect temp1 = MathManager::ConvertFRecttoRect(object1);
	SDL_Rect temp2 = MathManager::ConvertFRecttoRect(object2);
	return SDL_HasIntersection(&temp1, &temp2);
}

bool CollisionManager::CircleCircleCheck(const SDL_FPoint object1, const SDL_FPoint object2, const double r1, const double r2)
{
	return (MathManager::Distance((double)object1.x, (double)object2.x, (double)object1.y, (double)object2.y) < (r1 + r2));
}

bool CollisionManager::CircleAABBCheck(const SDL_FPoint object1, const double r, const SDL_FRect& object2)
{
	double x1 = (double)object1.x;
	double y1 = (double)object1.y;
	if (object1.x < object2.x)
		x1 = (double)object2.x;
	else if (object1.x > object2.x + object2.w)
		x1 = (double)object2.x + (double)object2.w;
	if (object1.y < object2.y)
		y1 = (double)object2.y;
	else if (object1.y > object2.y + object2.h)
		y1 = (double)object2.y + (double)object2.h;
	return CircleCircleCheck({ (float)x1, (float)y1 }, { (float)object1.x, (float)object1.y }, r);
}

bool CollisionManager::LinePointCheck(const SDL_FPoint object1_start, const SDL_FPoint object1_end, const SDL_FPoint object2)
{
	double DisttoStart = MathManager::Distance((double)object1_start.x, (double)object2.x, (double)object1_start.y, (double)object2.y);
	double DisttoEnd = MathManager::Distance((double)object1_end.x, (double)object2.x, (double)object1_end.y, (double)object2.y);
	 
	double LineLength;
	return false;
}
