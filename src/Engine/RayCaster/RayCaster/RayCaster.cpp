#include "RayCaster.h"

const double RayCaster::MAX_RAY_LENGTH = 24.f;

Intersection RayCaster::trace(Scene& scene, double startX, double startY, double angle, TraceTypes traceType, double maxRayLength)
{
	#pragma region Precalculate values
	// Direction
	const double DIR_X = cos(angle);
	const double DIR_Y = sin(angle);
	// Tile for checking
	int mapCheckX = int(startX);
	int mapCheckY = int(startY);
	// Distance that the ray should pass to go through one unit of the scene grid
	const double UNIT_STEP_X = sqrt(1 + (DIR_Y / DIR_X) * (DIR_Y / DIR_X));
	const double UNIT_STEP_Y = sqrt(1 + (DIR_X / DIR_Y) * (DIR_X / DIR_Y));
	// Length of the ray
	double rayLengthX = 0;
	double rayLengthY = 0;
	// Total distance
	double distance = 0.f;
	// Axis in which direction the ray is traced
	int stepX = 0;
	int stepY = 0;
	// Wall normals
	SurfaceTypes wallNormalX = SurfaceTypes::WALL_WEST;
	SurfaceTypes wallNormalY = SurfaceTypes::WALL_NORTH;
	// Init X values
	if (DIR_X > 0)
	{
		stepX = 1;
		rayLengthX = (double(mapCheckX) + 1.f - startX) * UNIT_STEP_X;
	}
	else
	{
		stepX = -1;
		rayLengthX = (startX - mapCheckX) * UNIT_STEP_X;
		wallNormalX = SurfaceTypes::WALL_EAST;
	}
	// Init Y values
	if (DIR_Y > 0)
	{
		stepY = 1;
		rayLengthY = (double(mapCheckY) + 1.f - startY) * UNIT_STEP_Y;
	}
	else
	{
		stepY = -1;
		rayLengthY = (startY - mapCheckY) * UNIT_STEP_Y;
		wallNormalY = SurfaceTypes::WALL_SOUTH;
	}
	#pragma endregion

	#pragma region Trace the ray
	while (distance < maxRayLength)
	{
		// The ray should go where the smallest length is
		bool goX = rayLengthX < rayLengthY;
		if (goX)
		{
			// Step in the X direction
			mapCheckX += stepX;
			distance = rayLengthX;
			rayLengthX += UNIT_STEP_X;
		}
		else
		{
			// Step in the Y direction
			mapCheckY += stepY;
			distance = rayLengthY;
			rayLengthY += UNIT_STEP_Y;
		}

		// Check the tile
		int levelTile = scene.wallIndexAt(mapCheckX, mapCheckY);

		// If found correcct intersection - initialize it
		if (checkTile(scene, levelTile, traceType))
			return Intersection(
				startX + DIR_X * distance, startY + DIR_Y * distance,
				distance, levelTile,
				(goX ? wallNormalX : wallNormalY));

	}
	#pragma endregion

	// Return empty intersection if the ray went too far
	return Intersection(startX + DIR_X * distance, startY + DIR_Y * distance,
		distance);
}

const bool RayCaster::checkTile(Scene& scene, int tileIndex, TraceTypes traceType)
{
	switch (traceType)
	{
		case TraceTypes::RENDERING:
		case TraceTypes::PHYSICS:
			return scene.wallTileFrom(tileIndex).isVisibleForTrace(traceType);
		default:
			return false;
	}
}
