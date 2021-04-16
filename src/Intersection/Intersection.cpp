#pragma once
#include "WallNormalDirection.h"

struct Intersection
{
	Intersection()
		: intersects(false), x(0), y(0), distance(0), tile(0), normalDirection(WallNormalDirection::NORTH) { };
	Intersection(double x, double y, double distance, int tile, WallNormalDirection normalDirection)
		: intersects(true), x(x), y(y), distance(distance), tile(tile), normalDirection(normalDirection) { };

	bool intersects;
	double x;
	double y;
	double distance;
	int tile;
	WallNormalDirection normalDirection;
};