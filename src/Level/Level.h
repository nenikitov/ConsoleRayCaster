#pragma once
#include <string>
#include <vector>
#include "../Tile/Tile.h"

class Level
{
	public:
		Level(std::string levelName);
		//Level(std::string levelName, std::string tileNames[]);
		//Tile getTileAt(unsigned int x, unsigned int y);
		//void updateTileAt(Tile tile, unsigned int x, unsigned int y);
		std::vector<std::vector<unsigned int>> tiles;
	private:
		
		//std::vector<std::vector<Tile>> tiles;
};