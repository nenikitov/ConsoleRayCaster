#pragma once
#include <string>
#include "Tile.h"
#include <vector>

class Level
{
	public:
		Level(std::string levelName, std::string tileNames[]);
		//Tile getTileAt(unsigned int x, unsigned int y);
		//void updateTileAt(Tile tile, unsigned int x, unsigned int y);
	private:
		std::vector<std::vector<Tile>> tiles;
};