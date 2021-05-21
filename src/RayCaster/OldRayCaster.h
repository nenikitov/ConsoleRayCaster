#pragma once
#include "../Level/Level.h"
#include "../Intersection/OldIntersection.h"

class OldRayCaster
{
	public:
		/// <summary>
		/// Initialize the ray caster
		/// </summary>
		/// <param name="level">The level where ray casting will be performed</param>
		/// <returns>The ray caster</returns>
		OldRayCaster(Level& level);
		/// <summary>
		/// Find intersection with the walls from the level
		/// </summary>
		/// <param name="startX">X location of the start point</param>
		/// <param name="startY">Y location of the start point</param>
		/// <param name="angle">Angle where the ray will be sent</param>
		/// <returns>The intersection data</returns>
		OldIntersection findIntersection(double startX, double startY, double angle);
	private:
		Level& level;
		const double MAX_RAY_LENGTH = 24.f;
};