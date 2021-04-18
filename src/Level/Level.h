#pragma once
#include <string>
#include <vector>
#include "../Tile/Tile.h"
#include "../JsonCpp/json/json.h"

class Level
{
	public:
		Level(std::string levelName);
		int tileIndexAt(unsigned int x, unsigned int y);
	private:
		int** wallData;
		int** floorData;
		int** ceilingData;
		unsigned int height;
		unsigned int* widths;
		int playerStartX;
		int playerStartY;
		double playerStartAngle;
};