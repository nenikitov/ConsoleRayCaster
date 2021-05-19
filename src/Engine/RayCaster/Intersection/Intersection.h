/*
#pragma once
#include "WallNormalDirection.h"

struct Intersection
{
	/// <summary>
	/// Construct default empty intersection (for if there is no intersection)
	/// </summary>
	/// <returns>Empty intersection</returns>
	Intersection()
		: intersects(false), x(0), y(0), distance(0), tile(0), normalDirection(WallNormalDirection::NORTH) { };
	/// <summary>
	/// Contstuct full intersection
	/// </summary>
	/// <param name="x">The X coordinate of an intersection</param>
	/// <param name="y">The Y coordinate of an intersection</param>
	/// <param name="distance">The distance from the start to the intersection</param>
	/// <param name="tile">The type of a tile that was intersected</param>
	/// <param name="normalDirection">The direction of the normal of the wall that was intersected</param>
	/// <returns></returns>
	Intersection(double x, double y, double distance, int tile, WallNormalDirection normalDirection)
		: intersects(true), x(x), y(y), distance(distance), tile(tile), normalDirection(normalDirection) { };

	/// <summary>
	/// If the intersection really occured
	/// </summary>
	bool intersects;
	/// <summary>
	/// The X coordinate of the intersection
	/// </summary>
	double x;
	/// <summary>
	/// The Y coordinate of the intersection
	/// </summary>
	double y;
	/// <summary>
	/// The distance from the start point to the coordinate of the intersection
	/// </summary>
	double distance;
	/// <summary>
	/// The index of a type of the tile that the intersection occured with
	/// </summary>
	int tile;
	/// <summary>
	/// The normal direction of the wall
	/// </summary>
	WallNormalDirection normalDirection;
};
*/