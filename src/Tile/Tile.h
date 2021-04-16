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
		CHAR_INFO sample(TileTypes type, WallNormalDirection normal, double x, double y, int lightness);
	private:
		unsigned short** textureBrightness;
		WORD** textureColors;
		unsigned short textureDimensions;

};