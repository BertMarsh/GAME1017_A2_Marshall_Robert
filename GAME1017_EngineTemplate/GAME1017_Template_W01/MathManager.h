#pragma once
#include <algorithm>
#include <cmath>

#include "SDL.h"

class MathManager
{
public: 
	static double Distance(const double& x1, const double& x2, const double& y1, const double& y2);
	static double AngleBetweenPoints(const double dy, const double dx);
	static void SetDeltas(const double angle, double& dx, double& dy, double fx = 1.0, double fy = 1.0);
	static double SetDeltaX(const double angle, double fx = 1.0);
	static double SetDeltaY(const double angle, double fy = 1.0);
	static double Deg2Rad(const double angle);
	static double Rad2Deg(const double angle);
	static SDL_Rect ConvertFRecttoRect(const SDL_FRect& r);
private:
	MathManager(){}
};

