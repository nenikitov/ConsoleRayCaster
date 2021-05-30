#include "Scene.h"

Scene::Scene()
{
	this->width = 0;
	this->height = 0;

	this->playerStartX = 0;
	this->playerStartY = 0;
	this->playerStartAngle = 0;
	
	this->wallData = nullptr;
	this->floorData = nullptr;
	this->ceilingData = nullptr;
	this->wallLookup = nullptr;
	this->floorLookup = nullptr;
	this->ceilingLookup = nullptr;

	this->wallLookupSize = 0;
	this->floorLookupSize = 0;
	this->ceilingLookupSize = 0;
}

void Scene::openLevelFile(std::string levelName)
{
	#pragma region Load JSON
	// Load JSON data from file
	Json::Value json;
	std::ifstream ifs;
	ifs.open("data/levels/" + levelName + ".lvl.json");
	Json::CharReaderBuilder builder;
	JSONCPP_STRING errs;

	// ERROR CATCHING - Invalid file
	if (!parseFromStream(builder, ifs, &json, &errs))
		throw std::invalid_argument(levelName + " - recieved invalid JSON file");
	#pragma endregion

	// Load player start data
	this->loadPlayerStart(json);
	// Load fog data
	this->loadFog(json);
	// Load tile lookup data
	this->loadLookup("wall", json, this->wallLookupSize, this->wallLookup);
	this->loadLookup("floor", json, this->floorLookupSize, this->floorLookup);
	this->loadLookup("ceiling", json, this->ceilingLookupSize, this->ceilingLookup);
	
	#pragma region Initialize level dimension
	if (!LoadingUtils::loadNotZero(json["tile"]["tileData"]["wall"].size(), this->height))
		throw std::invalid_argument("The height of a level is 0");

	// ERROR CATCHING - Inconsistent heights for wall, ceiling and floor data
	if (this->height != json["tile"]["tileData"]["floor"].size() ||  this->height != json["tile"]["tileData"]["ceiling"].size())
		throw std::invalid_argument(levelName + " - the height of a level is different for walls, ceiling and floor");

	this->width = json["tile"]["tileData"]["wall"][0].size();
	#pragma endregion

	#pragma region Initialize pointers
	this->wallData = new int* [this->height];
	this->floorData = new int* [this->height];
	this->ceilingData = new int* [this->height];
	#pragma endregion

	// Read level data row by row
	for (unsigned int y = 0; y < this->height; y++)
	{
		int rowWidth;

		if (!LoadingUtils::loadNotZero(json["tile"]["tileData"]["wall"][y].size(), rowWidth))
			throw std::invalid_argument("The width of a level on the line " + std::to_string(y) + " is 0");

		// ERROR CATCHING - Level is not rectangular
		if (rowWidth != this->width)
			throw std::invalid_argument("The level is not a rectangle. The width on the line " + std::to_string(y) + " is inconsistent");

		// ERROR CATCHING - Inconsistent widths for wall, ceiling and floor data
		if (rowWidth != json["tile"]["tileData"]["floor"][y].size() || rowWidth != json["tile"]["tileData"]["ceiling"][y].size())
			throw std::invalid_argument("The width of a level is different for walls, ceiling and floor on the line " + std::to_string(y));

		// Generate internal arrays for storing tile data
		this->wallData[y] = new int[rowWidth];
		this->floorData[y] = new int[rowWidth];
		this->ceilingData[y] = new int[rowWidth];

		// Read the tile data column by column (or tile by tile in this case)
		for (unsigned int x = 0; x < rowWidth; x++)
		{
			// Get wall tile data
			if (!LoadingUtils::loadCapped(json["tile"]["tileData"]["wall"][y][x].asInt(), this->wallData[y][x], 0, this->wallLookupSize - 1))
				throw std::invalid_argument("Wall index at " + std::to_string(x) + ", " + std::to_string(y) + " is out of range for wall lookup");

			// Get floor tile data
			if (!LoadingUtils::loadCapped(json["tile"]["tileData"]["floor"][y][x].asInt(), this->floorData[y][x], 0, this->floorLookupSize - 1))
				throw std::invalid_argument("Wall index at " + std::to_string(x) + ", " + std::to_string(y) + " is out of range for wall lookup");

			// Get ceiling tile data
			if (!LoadingUtils::loadCapped(json["tile"]["tileData"]["ceiling"][y][x].asInt(), this->ceilingData[y][x], 0, this->ceilingLookupSize - 1))
				throw std::invalid_argument("Wall index at " + std::to_string(x) + ", " + std::to_string(y) + " is out of range for wall lookup");
		}
	}
}

int Scene::wallIndexAt(unsigned int x, unsigned int y)
{
	if (y < this->height)
		if (x < this->width)
			return this->wallData[y][x];
	
	return 0;
}

int Scene::floorIndexAt(unsigned int x, unsigned int y)
{
	if (y < this->height)
		if (x < this->width)
			return this->floorData[y][x];

	return 0;
}

int Scene::ceilingIndexAt(unsigned int x, unsigned int y)
{
	if (y < this->height)
		if (x < this->width)
			return this->ceilingData[y][x];

	return 0;
}

Tile Scene::wallTileFrom(unsigned int i)
{
	if (i < 0 || i > this->wallLookupSize)
		return this->wallLookup[0];
	else
		return this->wallLookup[i];
}

Tile Scene::floorTileFrom(unsigned int i)
{
	if (i < 0 || i > this->floorLookupSize)
		return this->floorLookup[0];
	else
		return this->floorLookup[i];
}

Tile Scene::ceilingTileFrom(unsigned int i)
{
	if (i < 0 || i > this->ceilingLookupSize)
		return this->ceilingLookup[0];
	else
		return this->ceilingLookup[i];
}

SurfaceColors Scene::getFogColor()
{
	return this->fogColor;
}

double Scene::getFogSaturation()
{
	return this->fogSaturation;
}

double Scene::getFogBrightness()
{
	return this->fogBrightness;
}

int Scene::getFogDistance()
{
	return this->fogDistance;
}

SurfaceColors Scene::getSectorColor(unsigned int x, unsigned int y)
{
	if (y < this->height)
		if (x < this->width)
			return this->sectorColors[y][x];

	return SurfaceColors::BLACK;
}

double Scene::getSectorSaturation(unsigned int x, unsigned int y)
{
	if (y < this->height)
		if (x < this->width)
			return this->sectorSaturation[y][x];

	return 0;
}

double Scene::getSectorBrightness(unsigned int x, unsigned int y)
{
	if (y < this->height)
		if (x < this->width)
			return this->sectorBrightness[y][x];

	return 0;
}

void Scene::loadLookup(const char* TARGET, Json::Value& json, int& outSize, Tile*& outArray)
{
	if (!LoadingUtils::loadNotZero(json["tile"]["tileLookUp"][TARGET].size(), outSize))
		throw std::invalid_argument("Lookup for " + std::string(TARGET) + " is empty");

	outArray = (Tile*)malloc(outSize * sizeof(Tile));
	for (unsigned int i = 0; i < outSize; i++)
		outArray[i] = Tile(json["tile"]["tileLookUp"][TARGET][i].asString());
}

void Scene::loadPlayerStart(Json::Value& json)
{
	const double X = json["playerStart"]["x"].asDouble();
	const double Y = json["playerStart"]["y"].asDouble();
	double angle = json["playerStart"]["angle"].asInt() % 360;
	if (angle < 0)
		angle = 360 + angle;
	angle *= 0.017453292; // Transform degrees to radians

	this->playerStartX = X;
	this->playerStartY = Y;
	this->playerStartAngle = angle;
}

void Scene::loadFog(Json::Value& json)
{
	int fogColor;
	double fogSaturation;
	double fogBrightness;
	int fogDistance;
	// Color
	if (!LoadingUtils::loadCapped(json["lighting"]["fog"]["color"].asInt(), fogColor))
		throw std::invalid_argument("Fog color is invalid");

	// Saturation
	if (!LoadingUtils::loadCappedNormalized(json["lighting"]["fog"]["saturation"].asInt(), this->fogSaturation))
		throw std::invalid_argument("Fog saturation is invalid");

	// Brightness
	if (!LoadingUtils::loadCappedNormalized(json["lighting"]["fog"]["brightness"].asInt(), this->fogBrightness))
		throw std::invalid_argument("Fog saturation is invalid");

	if (!LoadingUtils::loadCapped(json["lighting"]["fog"]["distance"].asInt(), this->fogDistance, 0, 64))
		throw std::invalid_argument("Fog distance is invalid");
}

double Scene::getPlayerStartX()
{
	return this->playerStartX;
}

double Scene::getPlayerStartY()
{
	return this->playerStartY;
}

double Scene::getPlayerStartAngle()
{
	return this->playerStartAngle;
}
