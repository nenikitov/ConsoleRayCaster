#include "Tile.h"

Tile::Tile(std::string tileName)
{
	Json::Value json;
	std::ifstream ifs;
	ifs.open("data/tiles/" + tileName);
	Json::CharReaderBuilder builder;
	JSONCPP_STRING errs;
	if (!parseFromStream(builder, ifs, &json, &errs))
		throw std::invalid_argument("Recieved invalid JSON file");
	
	this->textureDimensions = json["rendering"]["brightness"].size();

	if (json["rendering"]["colors"].size() != this->textureDimensions)
		throw std::invalid_argument("Texture dimensions are not consistent");

	this->textureBrightness = new unsigned short*[this->textureDimensions];
	this->textureColors = new WORD* [this->textureDimensions];

	for (int y = 0; y < this->textureDimensions; y++)
	{
		this->textureBrightness[y] = new unsigned short [this->textureDimensions];
		this->textureColors[y] = new WORD [this->textureDimensions];

		if (json["rendering"]["brightness"][y].size() != this->textureDimensions || json["rendering"]["colors"][y].size())
			throw std::invalid_argument("Texture dimensions are not consistent");

		for (int x = 0; x < this->textureDimensions; x++)
		{
			this->textureBrightness[y][x] = json["rendering"]["brightness"][y][x].asInt();
			this->textureColors[y][x] = json["rendering"]["colors"][y][x].asInt();
		}
	}
}

CHAR_INFO Tile::sample(TileTypes type, WallNormalDirection normal, double x, double y, int lightness)
{
	return CHAR_INFO();
}

