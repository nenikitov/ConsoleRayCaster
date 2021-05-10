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
		/// <summary>
		/// Initialize the tile
		/// </summary>
		/// <param name="tileName">The name of the tile texture (should not contain ".tl.json")</param>
		/// <returns></returns>
		Tile(std::string tileName);
		/// <summary>
		/// Sample the texture of the current tile
		/// </summary>
		/// <param name="x">X coordinate of the texture</param>
		/// <param name="y">Y coordinate of the texture</param>
		/// <param name="lightness">Lightness multiplier</param>
		/// <param name="type">Type of the surface to sample</param>
		/// <param name="normal">Normal of the wall (Will be used if surface is a wall)</param>
		/// <returns>The character of the texture</returns>
		CHAR_INFO sampleTexture(double x, double y, double lightness, TileTypes type = TileTypes::WALL, WallNormalDirection normal = WallNormalDirection::NORTH);
	private:
		WORD processColor(unsigned short color, bool brighten = false);
		WCHAR lookupBrightnessChar(double brightness, TileTypes type);

		short** textureBrightness;
		unsigned short** textureColors;
		unsigned short textureDimensions;
		static const char wallCharLookUp[8];
		static const char floorCharLookUp[8];
		static const char ceilingCharLookUp[8];
};