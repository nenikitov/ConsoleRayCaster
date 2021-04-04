#include "RayCaster.h"
#include <iostream>
#include "../Intersection/Intersection.cpp"

RayCaster::RayCaster(Level& level) : level(level) {}

Intersection RayCaster::findIntersection(double startX, double startY, double angle)
{
	double dirX = cos(angle);
	double dirY = sin(angle);

	int mapCheckX = startX;
	int mapCheckY = startY;

	double unitStepX = sqrt(1 + (dirY / dirX) * (dirY / dirX));
	double unitStepY = sqrt(1 + (dirX / dirY) * (dirX / dirY));

	double rayLengthX = 0;
	double rayLengthY = 0;

	int stepX;
	int stepY;

	if (dirX < 0)
	{
		stepX = -1;
		rayLengthX = (startX - mapCheckX) * unitStepX;
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
	}
	else
	{
		stepY = 1;
		rayLengthY = ((double)mapCheckY + 1 - startY) * unitStepY;
	}

	double distance = 0.f;
	while (distance < this->MAX_RAY_LENGTH)
	{
		if (rayLengthX < rayLengthY)
		{
			mapCheckX += stepX;
			distance = rayLengthX;
			rayLengthX += unitStepX;
		}
		else
		{
			mapCheckY += stepY;
			distance = rayLengthY;
			rayLengthY += unitStepY;
		}

		int levelTile = this->level.tileAt(mapCheckX, mapCheckY);

		if (levelTile)
			return Intersection(startX + dirX * distance, startY + dirY * distance, distance, levelTile, WallNormalDirection::NORTH);
	}

	return Intersection();
}