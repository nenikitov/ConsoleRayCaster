#pragma once
#include <string>
#include <vector>
#include "../Tile/Tile.h"

class Level
{
	public:
		Level(std::string levelName);
		int tileAt(unsigned int x, unsigned int y);
		//Level(std::string levelName, std::string tileNames[]);
		//Tile getTileAt(unsigned int x, unsigned int y);
		//void updateTileAt(Tile tile, unsigned int x, unsigned int y);
	private:
		int** levelData;
		unsigned int* widths;
		unsigned int height;
};