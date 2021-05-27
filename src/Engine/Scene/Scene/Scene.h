#pragma once
#include <fstream>
#include "../Tile/Tile.h"
#include "../../../../lib/JsonCpp/json/json.h"

class Scene
{
	public:
		Scene();
		void openLevelFile(std::string levelName);
		int wallIndexAt(unsigned int x, unsigned int y);
		int floorIndexAt(unsigned int x, unsigned int y);
		int ceilingIndexAt(unsigned int x, unsigned int y);
		Tile wallTileFrom(unsigned int i);
		Tile floorTileFrom(unsigned int i);
		Tile ceilingTileFrom(unsigned int i);
		double getPlayerStartX();
		double getPlayerStartY();
		double getPlayerStartAngle();
	private:
		unsigned int height;
		unsigned int width;

		double playerStartX;
		double playerStartY;
		double playerStartAngle;

		int** wallData;
		int** floorData;
		int** ceilingData;
		Tile* wallLookup;
		Tile* floorLookup;
		Tile* ceilingLookup;
		unsigned int wallTiles;
		unsigned int floorTiles;
		unsigned int ceilingTiles;
};
