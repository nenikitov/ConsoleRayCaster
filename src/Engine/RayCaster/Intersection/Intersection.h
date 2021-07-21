#pragma once

#include "../../Render/FrameBuffer/CustomBufferTypes/SurfaceTypes.h"

struct Intersection
{
	public:
		Intersection();
		Intersection(double x, double y, double distance);
		Intersection(double x, double y, double distance, int tile, SurfaceTypes wallNormal);

		const bool VALID;
		const double X;
		const double Y;
		const double DISTANCE;
		const int TILE;
		const SurfaceTypes WALL_NORMAL;
};
