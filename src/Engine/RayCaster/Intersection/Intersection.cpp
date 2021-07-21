#include "Intersection.h"

Intersection::Intersection(
	double x, double y, double distance)
	: VALID(false),
	X(x),
	Y(y),
	DISTANCE(distance),
	TILE(-1),
	WALL_NORMAL(SurfaceTypes::NONE) { }

Intersection::Intersection(
	double x, double y, double distance, int tile, SurfaceTypes wallNormal)
		: VALID (true),
		X(x),
		Y(y),
		DISTANCE(distance),
		TILE(tile),
		WALL_NORMAL(wallNormal) { }
