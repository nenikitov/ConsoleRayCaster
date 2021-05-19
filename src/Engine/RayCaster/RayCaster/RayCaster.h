#pragma once
#include "../../Scene/Scene/Scene.h"
#include "../Intersection/Intersection.h"

class RayCaster
{
	public:
		Intersection findIntersection(double startX, double startY, double angle);
	private:
		const double MAX_RAY_LENGTH = 24.f;
};
