#pragma once
#include <fstream>
#include "../Tile/Tile.h"
#include "../../../../lib/JsonCpp/json/json.h"
#include "../../Utils/LoadingUtils.h"

class Scene
{
	public:
		#pragma region Initialization
		Scene();
		void openLevelFile(std::string levelName);
		#pragma endregion
		#pragma region Player start getters
		double getPlayerStartX();
		double getPlayerStartY();
		double getPlayerStartAngle();
		#pragma endregion
		#pragma region Tile getters
		// Tile index
		int wallIndexAt(unsigned int x, unsigned int y);
		int floorIndexAt(unsigned int x, unsigned int y);
		int ceilingIndexAt(unsigned int x, unsigned int y);
		// Tile object
		Tile wallTileFrom(unsigned int i);
		Tile floorTileFrom(unsigned int i);
		Tile ceilingTileFrom(unsigned int i);
		#pragma endregion
		#pragma region Lighting getters
		// Fog
		SurfaceColors getFogColor();
		double getFogSaturation();
		double getFogBrightness();
		double getFogDistance();
		// Sector lighting
		SurfaceColors getSectorColor(unsigned int x, unsigned int y);
		double getSectorSaturation(unsigned int x, unsigned int y);
		double getSectorBrightness(unsigned int x, unsigned int y);
		#pragma endregion
	private:
		#pragma region Dimensions
		unsigned int height;
		unsigned int width;
		#pragma endregion
		#pragma region Player start
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
		SurfaceColors fogColor;
		double fogSaturation;
		double fogBrightness;
		double fogDistance;
		// Sector
		SurfaceColors** sectorColors;
		double** sectorSaturation;
		double** sectorBrightness;
		#pragma endregion
		#pragma region Loading helper methods
		void loadLookUp(const char* TARGET, Json::Value& json, unsigned int& outSize, Tile*& outArray);
		void loadPlayerStart(Json::Value& json);
		#pragma endregion
};
