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
		#pragma region Dimensions
		unsigned int height;
		unsigned int width;
		#pragma endregion

		#pragma region Player
		double playerStartX;
		double playerStartY;
		double playerStartAngle;
		#pragma endregion

		#pragma region Tile
		// Look up
		unsigned int wallTiles;
		unsigned int floorTiles;
		unsigned int ceilingTiles;
		Tile* wallLookup;
		Tile* floorLookup;
		Tile* ceilingLookup;
		// Data
		int** wallData;
		int** floorData;
		int** ceilingData;
		#pragma endregion

		#pragma region Lighting
		// Fog
		SurfaceColors color;
		double saturation;
		double value;
		double distance;
		// Sector
		double** sectorBrightness;
		#pragma endregion
};
