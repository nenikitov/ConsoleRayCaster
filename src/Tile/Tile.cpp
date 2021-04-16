#include "Tile.h"

const char Tile::wallCharLookUp[8]    = { '.',  ':', ';', '+', '=', 'x', 'X', '#' };
const char Tile::floorCharLookUp[8]   = { '`', '\'', '"', '<', '?', 'f', '8', '@' };
const char Tile::ceilingCharLookUp[8] = { '.',  '-', '_', '(', '7', '}', 'E', '%' };

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

CHAR_INFO Tile::sampleTexture(double x, double y, int lightness, TileTypes type = TileTypes::WALL, WallNormalDirection normal = WallNormalDirection::NORTH)
{
	if (x > 1 || x < -1)
		x = fmod(x, 1);
	if (x < 0)
		x = 1 - x;

	if (x > 1 || x < -1)
		y = fmod(x, 1);
	if (y < 0)
		y = 1 - y;

	int intX = (int)(x * this->textureDimensions);
	int intY = (int)(y * this->textureDimensions);

	double relativeBrightness = this->textureBrightness[intX][intY] / 7 * lightness;
	relativeBrightness = min(max(0, relativeBrightness), 7);
	
	switch (type)
	{
		case WALL:
			if (normal == WallNormalDirection::NORTH || normal == WallNormalDirection::SOUTH)
				return {
					this->wallCharLookUp[(int)relativeBrightness], 
					this->textureColors[intX][intY] + 8 };
			else
				return {
					this->wallCharLookUp[(int)relativeBrightness],
					this->textureColors[intX][intY] };
		case FLOOR:
			return {
				this->floorCharLookUp[(int)relativeBrightness],
				this->textureColors[intX][intY] + 8 };
		case CEILING:
			return {
				this->ceilingCharLookUp[(int)relativeBrightness],
				this->textureColors[intX][intY] };
	}
}

