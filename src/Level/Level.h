#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "../Tile/Tile.h"
#include "../JsonCpp/json/json.h"

class Level
{
	public:
		Level(std::string levelName);
		int wallIndexAt(unsigned int x, unsigned int y);
		int floorIndexAt(unsigned int x, unsigned int y);
		int ceilingIndexAt(unsigned int x, unsigned int y);
		Tile wallTileFrom(unsigned int i);
		Tile floorTileFrom(unsigned int i);
		Tile ceilingTileFrom(unsigned int i);
		int getPlayerStartX();
		int getPlayerStartY();
		double getPlayerStartAngle();
	private:
		Tile* wallLookup;
		Tile* floorLookup;
		Tile* ceilingLookup;
		unsigned int wallTiles = 0;
		unsigned int floorTiles = 0;
		unsigned int ceilingTiles = 0;
		int** wallData;
		int** floorData;
		int** ceilingData;
		unsigned int height;
		unsigned int* widths;
		int playerStartX;
		int playerStartY;
		double playerStartAngle;
};