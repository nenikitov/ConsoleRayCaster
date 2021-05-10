#include "Tile.h"

const char Tile::wallCharLookUp[8]    = { '.',  ':', ';', '+', '=', 'x', 'X', '#' };
const char Tile::floorCharLookUp[8]   = { '`', '\'', '"', '<', 'f', '?', '8', '@' };
const char Tile::ceilingCharLookUp[8] = { '.',  '-', '_', '(', '7', '}', 'E', '%' };

Tile::Tile(std::string tileName)
{
	// Load JSON data from file
	Json::Value json;
	std::ifstream ifs;
	ifs.open("data/tiles/" + tileName + ".tl.json");
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
	this->textureBrightness = new short*[this->textureDimensions];
	this->textureColors = new unsigned short*[this->textureDimensions];

	// Read data line by line
	for (int y = 0; y < this->textureDimensions; y++)
	{
		// Initialize internal arrays
		this->textureBrightness[y] = new short[this->textureDimensions];
		this->textureColors[y] = new unsigned short[this->textureDimensions];

		// ERROR CATCHING - Inconsistent dimensions between color and brightness data
		if (json["rendering"]["brightness"][y].size() != this->textureDimensions || json["rendering"]["colors"][y].size() != this->textureDimensions)
			throw std::invalid_argument(tileName + " - texture dimensions are not square");

		for (int x = 0; x < this->textureDimensions; x++)
		{
			// Get brightness
			const short BRIGHTNESS = json["rendering"]["brightness"][y][x].asInt();
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
	// Limit the texture to be only from 0 to 1
	if (x > 1 || x < -1)
		x = fmod(x, 1);
	if (x < 0)
		x = 1 + x;

	if (y > 1 || y < -1)
		y = fmod(y, 1);
	if (y < 0)
		y = 1 + y;

	// Pixel to sample
	int intX = (int)(x * (this->textureDimensions));
	int intY = (int)(y * (this->textureDimensions));

	// Limit it to be from 0 to texture dimensions
	intX %= this->textureDimensions;
	intY %= this->textureDimensions;

	// Calculate the brightness level
	lightness = min(max(0, lightness), 1);
	double relativeBrightness = (double)this->textureBrightness[intY][intX] * lightness;
	
	// Get the color of the texture
	unsigned short color = this->textureColors[intY][intX];

	// Brighten the FLOOR or NORTH and SOUTH walls
	bool brighten = type == TileTypes::FLOOR || (type == TileTypes::WALL && (normal == WallNormalDirection::NORTH || normal == WallNormalDirection::SOUTH));

	WCHAR character = lookupBrightnessChar(relativeBrightness, type);
	WORD attribures = processColor(this->textureColors[intY][intX], brighten);

	return { character, attribures };
}

WORD Tile::processColor(unsigned short color, bool brighten)
{
	if (brighten)
	{
		// Verify if the color is gray (because for some reason bright and dark gray colors are switched)
		if (color != 7)
			return color + 8;
		else
			return 7;
	}
	else
	{
		// Verify if the color is gray (because for some reason bright and dark gray colors are switched)
		if (color != 7)
			return color;
		else
			return 8;
	}
}

WCHAR Tile::lookupBrightnessChar(double brightness, TileTypes type)
{
	int brightnessLookUp = min(brightness, 7);
	if (brightness >= 0)
	{
		switch (type)
		{
			case WALL:
				return (WCHAR)this->wallCharLookUp[brightnessLookUp];
			case FLOOR:
				return (WCHAR)this->floorCharLookUp[brightnessLookUp];
			case CEILING:
				return (WCHAR)this->ceilingCharLookUp[brightnessLookUp];
		}
	}
	else
		return (WCHAR)' ';
}
