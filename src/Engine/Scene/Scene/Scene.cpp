#include "Scene.h"

Scene::Scene(std::string levelName)
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
	this->playerStartX = json["player"]["x"].asInt();
	this->playerStartY = json["player"]["y"].asInt();
	this->playerStartAngle = (double)json["player"]["angle"].asInt() / 0.017453292; // Transform degrees to radians
	#pragma endregion

	#pragma region Load lookup data
	#pragma region Wall lookup
	// Get data from wall lookup
	const int WALL_LOOKUP_SIZE = json["tileLookUp"]["wall"].size();
	// ERROR CATCHING - No wall lookup present
	if (WALL_LOOKUP_SIZE == 0)
		throw std::invalid_argument(levelName + " - the lookup for walls is empty");

	this->wallTiles = WALL_LOOKUP_SIZE - 1;
	this->wallLookup = (Tile*) malloc(WALL_LOOKUP_SIZE * sizeof(Tile));
	for (unsigned int i = 0; i < WALL_LOOKUP_SIZE; i++)
		this->wallLookup[i] = Tile(json["tileLookUp"]["wall"][i].asString());
	#pragma endregion
#	pragma region Floor lookup
	// Get data from floor lookup
	const int FLOOR_LOOKUP_SIZE = json["tileLookUp"]["floor"].size();
	// ERROR CATCHING - No floor lookup present
	if (FLOOR_LOOKUP_SIZE == 0)
		throw std::invalid_argument(levelName + " - the lookup for floors is empty");
	
	this->floorTiles = FLOOR_LOOKUP_SIZE - 1;
	this->floorLookup = (Tile*)malloc(FLOOR_LOOKUP_SIZE * sizeof(Tile));
	for (unsigned int i = 0; i < FLOOR_LOOKUP_SIZE; i++)
		this->floorLookup[i] = Tile(json["tileLookUp"]["floor"][i].asString());
	#pragma endregion
	#pragma region Ceiling lookup
	// Get data from ceiling lookup
	const int CEILING_LOOKUP_SIZE = json["tileLookUp"]["ceiling"].size();
	// ERROR CATCHING - No ceiling lookup present
	if (CEILING_LOOKUP_SIZE == 0)
		throw std::invalid_argument(levelName + " - the lookup for ceilings is empty");

	this->ceilingTiles = CEILING_LOOKUP_SIZE - 1;
	this->ceilingLookup = (Tile*)malloc(CEILING_LOOKUP_SIZE * sizeof(Tile));
	for (unsigned int i = 0; i < CEILING_LOOKUP_SIZE; i++)
		this->ceilingLookup[i] = Tile(json["tileLookUp"]["ceiling"][i].asString());
	#pragma endregion
	#pragma endregion

	#pragma region Initialize level height
	// Get height of the level
	this->height = json["tileData"]["wall"].size();
	// ERROR CATCHING - Height is 0
	if (this->height == 0)
		throw std::invalid_argument(levelName + " - the height of a level is 0");

	// ERROR CATCHING - Inconsistent heights for wall, ceiling and floor data
	if (this->height != json["tileData"]["floor"].size() ||  this->height != json["tileData"]["ceiling"].size())
		throw std::invalid_argument(levelName + " - the height of a level is different for walls, ceiling and floor");
	#pragma endregion

	#pragma region Initialize level width
	this->width = json["tileData"]["wall"][0].size();
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
		const unsigned int WIDTH = json["tileData"]["wall"][y].size();

		// ERROR CATCHING - Width is 0
		if (WIDTH == 0)
			throw std::invalid_argument(levelName + " - the width of a level on the line " + std::to_string(y) + " is 0");

		// ERROR CATCHING - Widths are inconsistent
		if (WIDTH != this->width)
			throw std::invalid_argument(levelName + " - the width of a level on the line " + std::to_string(y) + " is inconsistent");

		// ERROR CATCHING - Inconsistent widths for wall, ceiling and floor data
		if (WIDTH != json["tileData"]["floor"][y].size() || WIDTH != json["tileData"]["ceiling"][y].size())
			throw std::invalid_argument(levelName + " - the width of a level is different for walls, ceiling and floor on the line " + std::to_string(y));

		// Generate internal arrays for storing tile data
		this->wallData[y] = new int[WIDTH];
		this->floorData[y] = new int[WIDTH];
		this->ceilingData[y] = new int[WIDTH];

		// Read the tile data column by column
		for (unsigned int x = 0; x < WIDTH; x++)
		{
			// Get wall tile data
			const int WALL_DATA = json["tileData"]["wall"][y][x].asInt();
			// ERROR CATCHING - Invalid tile data
			if (WALL_DATA < 0)
				throw std::invalid_argument(levelName + " - negative wall data at " + std::to_string(x) + ", " + std::to_string(y));
			if (WALL_DATA > this->wallTiles)
				throw std::invalid_argument(levelName + " - unknown lookup for wall data at " + std::to_string(x) + ", " + std::to_string(y));
			
			this->wallData[y][x] = WALL_DATA;

			// Get floor tile data
			const int FLOOR_DATA = json["tileData"]["floor"][y][x].asInt();
			// ERROR CATCHING - Invalid tile data
			if (FLOOR_DATA < 0)
				throw std::invalid_argument(levelName + " - invalid floor data index at " + std::to_string(x) + ", " + std::to_string(y));

			this->floorData[y][x] = FLOOR_DATA;

			// Get ceiling tile data
			const int CEILING_DATA = json["tileData"]["ceiling"][y][x].asInt();
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

int Scene::getPlayerStartX()
{
	return this->playerStartX;
}

int Scene::getPlayerStartY()
{
	return this->playerStartY;
}

double Scene::getPlayerStartAngle()
{
	return this->playerStartAngle;
}
