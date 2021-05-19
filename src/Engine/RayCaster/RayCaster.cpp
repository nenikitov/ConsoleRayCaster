/*

#include "RayCaster.h"
#include <iostream>
#include "../Intersection/Intersection.h"

RayCaster::RayCaster(Level& level) : level(level) {}

Intersection RayCaster::findIntersection(double startX, double startY, double angle)
{
	#pragma region Initialize and precalculate variables
	// Direction
	double dirX = cos(angle);
	double dirY = sin(angle);
	// Tile for checking
	int mapCheckX = startX;
	int mapCheckY = startY;
	// The distance that the ray should pass to go through one unit of the level
	double unitStepX = sqrt(1 + (dirY / dirX) * (dirY / dirX));
	double unitStepY = sqrt(1 + (dirX / dirY) * (dirX / dirY));
	// Length of the ray
	double rayLengthX = 0;
	double rayLengthY = 0;
	// Axis in which direction the ray will be traced
	int stepX;
	int stepY;
	// Wall directions
	WallNormalDirection wallNormalX = WallNormalDirection::WEST;
	WallNormalDirection wallNormalY = WallNormalDirection::NORTH;

	if (dirX < 0)
	{
		stepX = -1;
		rayLengthX = (startX - mapCheckX) * unitStepX;
		wallNormalX = WallNormalDirection::EAST;
	}
	else
	{
		stepX = 1;
		rayLengthX = ((double)mapCheckX + 1 - startX) * unitStepX;
	}

	if (dirY < 0)
	{
		stepY = -1;
		rayLengthY = (startY - mapCheckY) * unitStepY;
		wallNormalY = WallNormalDirection::SOUTH;
	}
	else
	{
		stepY = 1;
		rayLengthY = ((double)mapCheckY + 1 - startY) * unitStepY;
	}
	#pragma endregion

	double distance = 0.f;
	#pragma region Trace the ray
	while (distance < this->MAX_RAY_LENGTH)
	{		
		// The ray should go where the smallest length is
		bool goX = rayLengthX < rayLengthY;
		if (goX)
		{
			// Step in the X direction
			mapCheckX += stepX;
			distance = rayLengthX;
			rayLengthX += unitStepX;
		}
		else
		{
			// Step in the Y direction
			mapCheckY += stepY;
			distance = rayLengthY;
			rayLengthY += unitStepY;
		}

		// Check the tile
		int levelTile = this->level.wallIndexAt(mapCheckX, mapCheckY);

		// If found intersection - initialize it
		if (levelTile)
			return Intersection(startX + dirX * distance, startY + dirY * distance, distance, levelTile, (goX ? wallNormalX : wallNormalY));
			
	}
	#pragma endregion

	// Return empty intersection if the ray went too far
	return Intersection();
}
*/
