#pragma once

#include "../../Scene/Scene/Scene.h"
#include "../Intersection/Intersection.h"

class RayCaster
{
	public:
		static Intersection trace(Scene& scene, double startX, double startY, double angle, double maxRayLength = MAX_RAY_LENGTH);
	private:
		const static double MAX_RAY_LENGTH;
};

const double RayCaster::MAX_RAY_LENGTH = 24.f;
