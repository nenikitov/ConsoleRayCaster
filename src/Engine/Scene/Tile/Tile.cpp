#include "Tile.h"

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
		throw std::invalid_argument(tileName + " texture - recieved invalid JSON file");

	// Set texture dimensions
	if (!LoadingUtils::loadNotZero(json["rendering"]["brightness"].size(), this->textureDimensions))
		throw std::invalid_argument(tileName + " - empty tile texture data found");

	// ERROR CATCHING - Inconsistent dimensions between color and brightness data
	if (json["rendering"]["colors"].size() != this->textureDimensions)
		throw std::invalid_argument(tileName + " - brightness and color texture data have different sizes");

	// Initialize internal arrays
	this->textureBrightness = new double*[this->textureDimensions];
	this->textureColors = new SurfaceColors*[this->textureDimensions];

	// Read data column by column
	for (int y = 0; y < this->textureDimensions; y++)
	{
		// Initialize internal arrays
		this->textureBrightness[y] = new double[this->textureDimensions];
		this->textureColors[y] = new SurfaceColors[this->textureDimensions];

		// ERROR CATCHING - Inconsistent dimensions between color and brightness data
		if (json["rendering"]["brightness"][y].size() != this->textureDimensions || json["rendering"]["colors"][y].size() != this->textureDimensions)
			throw std::invalid_argument(tileName + " - texture dimensions are not square");

		for (int x = 0; x < this->textureDimensions; x++)
		{
			// Get brightness
			if (!LoadingUtils::loadCappedNormalized(json["rendering"]["brightness"][y][x].asInt(), this->textureBrightness[y][x], -7, 7))
				throw std::invalid_argument(tileName + " - brightness is illegal at " + std::to_string(x) + ", " + std::to_string(y));

			// Get color
			int color;
			if (!LoadingUtils::loadCapped(json["rendering"]["colors"][y][x].asInt(), color))
				throw std::invalid_argument(tileName + " - color is illegal at " + std::to_string(x) + ", " + std::to_string(y));
			this->textureColors[y][x] = (SurfaceColors) color;
		}
	}
}

double Tile::sampleBrightness(double x, double y)
{
	int sampleX = 0;
	int sampleY = 0;
	this->treatCoords(x, y, sampleX, sampleY);

	return abs(this->textureBrightness[sampleY][sampleX]);
}

bool Tile::sampleReceiveLighting(double x, double y)
{
	int sampleX = 0;
	int sampleY = 0;
	this->treatCoords(x, y, sampleX, sampleY);

	return this->textureBrightness[sampleY][sampleX] >= 0;
}

SurfaceColors Tile::sampleColor(double x, double y)
{
	int sampleX = 0;
	int sampleY = 0;
	this->treatCoords(x, y, sampleX, sampleY);

	return this->textureColors[sampleY][sampleX];
}

void Tile::treatCoords(double x, double y, int& outX, int& outY)
{
	outX = (int)floor(x * this->textureDimensions) % this->textureDimensions;
	outY = (int)floor(y * this->textureDimensions) % this->textureDimensions;

	if (outX < 0)
		outX = this->textureDimensions + outX;

	if (outY < 0)
		outY = this->textureDimensions + outY;
}
