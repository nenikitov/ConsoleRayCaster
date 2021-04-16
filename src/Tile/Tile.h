#pragma once
#include <string>

class Tile
{
	public:
		Tile(std::string tileName);
		CHAR_INFO sample();
	private:
		unsigned short** textureBrightness;
		WORD** textureColors;
};