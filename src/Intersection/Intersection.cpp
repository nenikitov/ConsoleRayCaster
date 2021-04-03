#pragma once
#include "WallNormalDirection.cpp"

struct Intersection
{
	bool inersects;
	double x;
	double y;
	double distance;
	int tile;
	WallNormalDirection normalDirection;
};