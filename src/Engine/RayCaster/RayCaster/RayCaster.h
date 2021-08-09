#pragma once

#include "../../Scene/Scene/Scene.h"
#include "../Intersection/Intersection.h"
#include "../TraceTypes/TraceTypes.h"

class RayCaster
{
	public:
		static Intersection trace(Scene& scene, double startX, double startY, double angle, TraceTypes traceType = TraceTypes::RENDERING, double maxRayLength = MAX_RAY_LENGTH);
	private:
		const static double MAX_RAY_LENGTH;
		const static bool checkTile(Scene& scene, int tileIndex, TraceTypes traceType);
};
