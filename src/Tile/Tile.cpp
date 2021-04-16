#include "Tile.h"

Tile::Tile(std::string tileName)
{
	Json::Value json;
	std::ifstream ifs;
	ifs.open("data/tiles/" + tileName);
	Json::CharReaderBuilder builder;
	JSONCPP_STRING errs;
	if (!parseFromStream(builder, ifs, &json, &errs))
	{
		throw std::invalid_argument("Recieved invalid JSON file");
	}

	
}

CHAR_INFO Tile::sample(TileTypes type, double x, double y, int lightness)
{
	return CHAR_INFO();
}
