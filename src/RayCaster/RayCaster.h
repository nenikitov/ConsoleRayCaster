#pragma once
#include "../Level/Level.h"
#include "../Intersection/Intersection.cpp"

class RayCaster
{
	public:
		RayCaster(Level& level);
		Intersection findIntersection(double startX, double startY, double angle);
	private:
		Level& level;
		const double MAX_RAY_LENGTH = 24.f;
};