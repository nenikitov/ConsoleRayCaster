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

	this->wallTiles = 0;
	this->floorTiles = 0;
	this->ceilingTiles = 0;
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

	#pragma region Load player data
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
	#pragma endregion

	#pragma region Load fog data
	{
		const int FOG_COLOR = json["lighting"]["fog"]["color"].asInt();
		const int FOG_SATURATION = json["lighting"]["fog"]["saturation"].asInt();
		const int FOG_BRIGHTNESS = json["lighting"]["fog"]["brightness"].asInt();
		const double FOG_DISTANCE = json["lighting"]["fog"]["distance"].asDouble();
		// Color
		if (FOG_COLOR < 0 || FOG_COLOR > 7)
			throw std::invalid_argument(levelName + " - fog color is invalid");
		else
			this->fogColor = (SurfaceColors)FOG_COLOR;
		// Saturation
		if (FOG_SATURATION < 0 || FOG_SATURATION > 7)
			throw std::invalid_argument(levelName + " - fog saturation is invalid");
		else
			this->fogSaturation = FOG_SATURATION / 7.f;
		// Brightness
		if (FOG_BRIGHTNESS < 0 || FOG_BRIGHTNESS > 7)
			throw std::invalid_argument(levelName + " - fog brightness is invalid");
		else
			this->fogBrightness = FOG_BRIGHTNESS / 7.f;
		// Distance
		if (FOG_DISTANCE < 0)
			throw std::invalid_argument(levelName + " - fog distance is invalid");
		else
			this->fogDistance = FOG_DISTANCE;
	}
	#pragma endregion

	#pragma region Load lookup data
	this->loadLookUp("wall", json, this->wallTiles, this->wallLookup);
	this->loadLookUp("floor", json, this->floorTiles, this->floorLookup);
	this->loadLookUp("ceiling", json, this->ceilingTiles, this->ceilingLookup);
	#pragma endregion
	#pragma region Initialize level height
	// Get height of the level
	this->height = json["tile"]["tileData"]["wall"].size();
	// ERROR CATCHING - Height is 0
	if (this->height == 0)
		throw std::invalid_argument(levelName + " - the height of a level is 0");

	// ERROR CATCHING - Inconsistent heights for wall, ceiling and floor data
	if (this->height != json["tile"]["tileData"]["floor"].size() ||  this->height != json["tile"]["tileData"]["ceiling"].size())
		throw std::invalid_argument(levelName + " - the height of a level is different for walls, ceiling and floor");
	#pragma endregion

	#pragma region Initialize level width
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
		// Get width of the level
		const unsigned int WIDTH = json["tile"]["tileData"]["wall"][y].size();

		// ERROR CATCHING - Width is 0
		if (WIDTH == 0)
			throw std::invalid_argument(levelName + " - the width of a level on the line " + std::to_string(y) + " is 0");

		// ERROR CATCHING - Widths are inconsistent
		if (WIDTH != this->width)
			throw std::invalid_argument(levelName + " - the width of a level on the line " + std::to_string(y) + " is inconsistent");

		// ERROR CATCHING - Inconsistent widths for wall, ceiling and floor data
		if (WIDTH != json["tile"]["tileData"]["floor"][y].size() || WIDTH != json["tile"]["tileData"]["ceiling"][y].size())
			throw std::invalid_argument(levelName + " - the width of a level is different for walls, ceiling and floor on the line " + std::to_string(y));

		// Generate internal arrays for storing tile data
		this->wallData[y] = new int[WIDTH];
		this->floorData[y] = new int[WIDTH];
		this->ceilingData[y] = new int[WIDTH];

		// Read the tile data column by column
		for (unsigned int x = 0; x < WIDTH; x++)
		{
			// Get wall tile data
			const int WALL_DATA = json["tile"]["tileData"]["wall"][y][x].asInt();
			// ERROR CATCHING - Invalid tile data
			if (WALL_DATA < 0)
				throw std::invalid_argument(levelName + " - negative wall data at " + std::to_string(x) + ", " + std::to_string(y));
			if (WALL_DATA > this->wallTiles)
				throw std::invalid_argument(levelName + " - unknown lookup for wall data at " + std::to_string(x) + ", " + std::to_string(y));
			
			this->wallData[y][x] = WALL_DATA;

			// Get floor tile data
			const int FLOOR_DATA = json["tile"]["tileData"]["floor"][y][x].asInt();
			// ERROR CATCHING - Invalid tile data
			if (FLOOR_DATA < 0)
				throw std::invalid_argument(levelName + " - invalid floor data index at " + std::to_string(x) + ", " + std::to_string(y));

			this->floorData[y][x] = FLOOR_DATA;

			// Get ceiling tile data
			const int CEILING_DATA = json["tile"]["tileData"]["ceiling"][y][x].asInt();
			// ERROR CATCHING - Invalid tile data
			if (CEILING_DATA < 0)
				throw std::invalid_argument(levelName + " - invalid ceiling data index at " + std::to_string(x) + ", " + std::to_string(y));

			this->ceilingData[y][x] = CEILING_DATA;
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
	if (i < 0 || i > this->wallTiles)
		return this->wallLookup[0];
	else
		return this->wallLookup[i];
}

Tile Scene::floorTileFrom(unsigned int i)
{
	if (i < 0 || i > this->floorTiles)
		return this->floorLookup[0];
	else
		return this->floorLookup[i];
}

Tile Scene::ceilingTileFrom(unsigned int i)
{
	if (i < 0 || i > this->ceilingTiles)
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

double Scene::getFogDistance()
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

void Scene::loadLookUp(const char* TARGET, Json::Value& json, unsigned int& outSize, Tile*& outArray)
{
	const int LOOKUP_SIZE = json["tile"]["tileLookUp"][TARGET].size();
	// ERROR CATCHING - No lookup present
	if (LOOKUP_SIZE == 0)
		throw std::invalid_argument("The lookup for " + std::string(TARGET) + " is empty");

	outSize = LOOKUP_SIZE - 1;
	outArray = (Tile*)malloc(LOOKUP_SIZE * sizeof(Tile));
	for (unsigned int i = 0; i < LOOKUP_SIZE; i++)
		outArray[i] = Tile(json["tile"]["tileLookUp"][TARGET][i].asString());
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
