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
		int** levelData;
		unsigned int* widths;
		unsigned int height;
		int playerStartX;
		int playerStartY;
		double playerStartAngle;
};