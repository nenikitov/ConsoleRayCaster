#pragma once
#include <string>
#include <Windows.h>
#include <fstream>
#include <iostream>
#include "TileTypes.h"
#include "../JsonCpp/json/json.h"
#include "../Intersection/WallNormalDirection.h"

class Tile
{
	public:
		Tile(std::string tileName);
		CHAR_INFO sampleTexture(double x, double y, int lightness, TileTypes type = TileTypes::WALL, WallNormalDirection normal = WallNormalDirection::NORTH);
	private:
		unsigned short** textureBrightness;
		WORD** textureColors;
		unsigned short textureDimensions;
		static const char wallCharLookUp[8];
		static const char floorCharLookUp[8];
		static const char ceilingCharLookUp[8];
};