#include "Tile.h"

const char Tile::wallCharLookUp[8]    = { '.',  ':', ';', '+', '=', 'x', 'X', '#' };
const char Tile::floorCharLookUp[8]   = { '`', '\'', '"', '<', 'f', '?', '8', '@' };
const char Tile::ceilingCharLookUp[8] = { '.',  '-', '_', '(', '7', '}', 'E', '%' };

Tile::Tile(std::string tileName)
{
	// Load JSON data from file
	Json::Value json;
	std::ifstream ifs;
	ifs.open("data/tiles/" + tileName);
	Json::CharReaderBuilder builder;
	JSONCPP_STRING errs;

	// ERROR CATCHING - Invalid file
	if (!parseFromStream(builder, ifs, &json, &errs))
		throw std::invalid_argument(tileName + " - recieved invalid JSON file");

	// Set texture dimensions 
	this->textureDimensions = json["rendering"]["brightness"].size();

	// ERROR CATCHING - Dimensions are 0
	if (this->textureDimensions == 0)
		throw std::invalid_argument(tileName + " - the height of a level is 0");

	// ERROR CATCHING - Inconsistent dimensions between color and brightness data
	if (json["rendering"]["colors"].size() != this->textureDimensions)
		throw std::invalid_argument(tileName + " - brightness and color data have different sizes");

	// Initialize internal arrays
	this->textureBrightness = new unsigned short*[this->textureDimensions];
	this->textureColors = new unsigned short*[this->textureDimensions];

	// Read data line by line
	for (int y = 0; y < this->textureDimensions; y++)
	{
		// Initialize internal arrays
		this->textureBrightness[y] = new unsigned short[this->textureDimensions];
		this->textureColors[y] = new unsigned short[this->textureDimensions];

		// ERROR CATCHING - Inconsistent dimensions between color and brightness data
		if (json["rendering"]["brightness"][y].size() != this->textureDimensions || json["rendering"]["colors"][y].size() != this->textureDimensions)
			throw std::invalid_argument(tileName + " - texture dimensions are not square");

		for (int x = 0; x < this->textureDimensions; x++)
		{
			// Get brightness
			const short BRIGHTNESS = json["rendering"]["brightness"][y][x].asInt();
			// ERROR CATCHING - Brightness data is invalid
			if (BRIGHTNESS < 0)
				throw std::invalid_argument(tileName + " - brightness is illegal at " + std::to_string(x) + ", " + std::to_string(y));
			this->textureBrightness[y][x] = BRIGHTNESS;

			// Get color
			const short COLOR = json["rendering"]["colors"][y][x].asInt();
			// ERROR CATCHING - Color data is invalid
			if (COLOR > 7 || COLOR < 0)
				throw std::invalid_argument(tileName + " - color is illegal at " + std::to_string(x) + ", " + std::to_string(y));

			this->textureColors[y][x] = COLOR;
		}
	}
}

CHAR_INFO Tile::sampleTexture(double x, double y, double lightness, TileTypes type, WallNormalDirection normal)
{
	if (x > 1 || x < -1)
		x = fmod(x, 1);
	if (x < 0)
		x = 1 + x;

	if (y > 1 || y < -1)
		y = fmod(y, 1);
	if (y < 0)
		y = 1 + y;

	int intX = (int)(x * (this->textureDimensions));
	int intY = (int)(y * (this->textureDimensions));

	intX %= this->textureDimensions;
	intY %= this->textureDimensions;

	double relativeBrightness = (double)this->textureBrightness[intY][intX] * lightness;
	relativeBrightness = min(max(0, relativeBrightness), 7);

	int brightnessLookUp = relativeBrightness;
	unsigned short color = this->textureColors[intY][intX];

	switch (type)
	{
		case WALL:
			if (normal == WallNormalDirection::NORTH || normal == WallNormalDirection::SOUTH)
				return {
					(WCHAR)this->wallCharLookUp[brightnessLookUp],
					processColor(this->textureColors[intY][intX], true) };
			else
				return {
					(WCHAR)this->wallCharLookUp[brightnessLookUp],
					processColor(this->textureColors[intY][intX]) };
		case FLOOR:
			return {
				(WCHAR)this->floorCharLookUp[brightnessLookUp],
				processColor(this->textureColors[intY][intX], true) };
		case CEILING:
			return {
				(WCHAR)this->ceilingCharLookUp[brightnessLookUp],
				processColor(this->textureColors[intY][intX]) };
	}
}

WORD Tile::processColor(unsigned short color, bool brighten)
{
	if (brighten)
	{
		if (color != 7)
			return color + 8;
		else
			return 7;
	}
	else
	{
		if (color != 7)
			return color;
		else
			return 8;
	}
}
