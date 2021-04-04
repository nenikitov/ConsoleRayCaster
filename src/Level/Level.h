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
		std::vector<std::vector<unsigned int>> tiles;
		//std::vector<std::vector<Tile>> tiles;
		const int level[16][16] =
		{
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1},
			{1, 0, 1, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1},
			{1, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1},
			{1, 0, 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 1, 2, 3, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 1, 2, 3, 4, 0, 0, 0, 0, 5, 5, 0, 0, 0, 1},
			{1, 0, 1, 2, 3, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 1},
			{1, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		};
};