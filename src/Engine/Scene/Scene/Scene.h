#pragma once
#include <fstream>
#include "../Tile/Tile.h"
#include "../../../../lib/JsonCpp/json/json.h"
#include "../../Utils/LoadingUtils/LoadingUtils.h"

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
		int wallIndexAt(double x, double y);
		int floorIndexAt(double x, double y);
		int ceilingIndexAt(double x, double y);
		// Tile object
		Tile wallTileFrom(int i);
		Tile floorTileFrom(int i);
		Tile ceilingTileFrom(int i);
		#pragma endregion
		#pragma region Lighting getters
		// Fog
		double getFogBrightness();
		int getFogDistance();
		// Sector lighting
		double getSectorBrightness(double x, double y);
		#pragma endregion
	private:
		#pragma region Dimensions
		int height;
		int width;
		#pragma endregion
		#pragma region Player start
		double playerStartX;
		double playerStartY;
		double playerStartAngle;
		#pragma endregion
		#pragma region Tile
		// Look up
		int wallLookupSize;
		int floorLookupSize;
		int ceilingLookupSize;
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
		double fogBrightness;
		int fogDistance;
		// Sector
		double** sectorBrightness;
		#pragma endregion
		#pragma region Loading helper methods
		void loadLookup(const char* TARGET, Json::Value& json, int& outSize, Tile*& outArray);
		void loadPlayerStart(Json::Value& json);
		void loadFog(Json::Value& json);
		void initLevelDimensions(Json::Value& json);
		#pragma endregion
};
