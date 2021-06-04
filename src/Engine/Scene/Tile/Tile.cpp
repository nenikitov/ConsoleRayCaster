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
			const short BRIGHTNESS = json["rendering"]["brightness"][y][x].asInt();

			if (abs(BRIGHTNESS) > 7)
				throw std::invalid_argument(tileName + " - brightness is illegal at " + std::to_string(x) + ", " + std::to_string(y));

			this->textureBrightness[y][x] = BRIGHTNESS / 7.f;

			// Get color
			unsigned char COLOR = json["rendering"]["colors"][y][x].asInt();
			// ERROR CATCHING - Color data is invalid
			if (COLOR < 0 || COLOR > 7)
				throw std::invalid_argument(tileName + " - color is illegal at " + std::to_string(x) + ", " + std::to_string(y));

			this->textureColors[y][x] = static_cast<SurfaceColors>(COLOR);
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
