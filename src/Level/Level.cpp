#include "Level.h"

Level::Level(std::string levelName)
{
	#pragma region Load JSON
	// Load JSON data from file
	Json::Value json;
	std::ifstream ifs;
	ifs.open("data/levels/" + levelName);
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

	#pragma region Load lookup
	#pragma region Wall lookup
	// Get data from wall lookup
	const int WALL_LOOKUP_SIZE = json["tileLookUp"]["wall"].size();
	// ERROR CATCHING - No wall lookup present
	if (WALL_LOOKUP_SIZE == 0)
		throw std::invalid_argument(levelName + " - the lookup for walls is empty");

	this->wallLookup = (Tile*) malloc(WALL_LOOKUP_SIZE * sizeof(Tile));
	this->wallTiles = WALL_LOOKUP_SIZE - 1;
	for (unsigned int i = 0; i < WALL_LOOKUP_SIZE; i++)
		this->wallLookup[i] = Tile(json["tileLookUp"]["wall"][i].asString() + ".tl.json");
	#pragma endregion
	#pragma endregion

	#pragma region Initialize height
	// Get height of the level
	this->height = json["tileData"]["wall"].size();
	// ERROR CATCHING - Height is 0
	if (this->height == 0)
		throw std::invalid_argument(levelName + " - the height of a level is 0");

	// ERROR CATCHING - Inconsistent heights for wall, ceiling and floor data
	if (this->height != json["tileData"]["floor"].size() ||  this->height != json["tileData"]["ceiling"].size())
		throw std::invalid_argument(levelName + " - the height of a level is different for walls, ceiling and floor");
	#pragma endregion

	#pragma region Initialize pointers
	this->wallData = new int* [this->height];
	this->floorData = new int* [this->height];
	this->ceilingData = new int* [this->height];
	this->widths = new unsigned int[height];
	#pragma endregion

	// Read level data row by row
	for (unsigned int y = 0; y < this->height; y++)
	{
		// Get width of the level
		const unsigned int WIDTH = json["tileData"]["wall"][y].size();

		// ERROR CATCHING - Width is 0
		if (WIDTH == 0)
			throw std::invalid_argument(levelName + " - the width of a level on the line " + std::to_string(y) + " is 0");

		// ERROR CATCHING - Inconsistent widths for wall, ceiling and floor data
		if (WIDTH != json["tileData"]["floor"][y].size() || this->height != json["tileData"]["ceiling"][y].size())
			throw std::invalid_argument(levelName + " - the width of a level is different for walls, ceiling and floor on the line " + std::to_string(y));

		// Assign it to internal arrays
		this->widths[y] = WIDTH;
		this->wallData[y] = new int[WIDTH];
		this->floorData[y] = new int[WIDTH];
		this->ceilingData[y] = new int[WIDTH];

		// Read the tile data
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
			if (WALL_DATA < 0)
				throw std::invalid_argument(levelName + " - invalid floor data index at " + std::to_string(x) + ", " + std::to_string(y));
			this->floorData[y][x] = FLOOR_DATA;

			// Get ceiling tile data
			const int CEILING_DATA = json["tileData"]["ceiling"][y][x].asInt();
			// ERROR CATCHING - Invalid tile data
			if (WALL_DATA < 0)
				throw std::invalid_argument(levelName + " - invalid ceiling data index at " + std::to_string(x) + ", " + std::to_string(y));
			this->ceilingData[y][x] = CEILING_DATA;
		}
	}
}

int Level::wallIndexAt(unsigned int x, unsigned int y)
{
	if (y < this->height)
		if (x < this->widths[y])
			return this->wallData[y][x];
	
	return 0;
}

int Level::floorIndexAt(unsigned int x, unsigned int y)
{
	if (y < this->height)
		if (x < this->widths[y])
			return this->floorData[y][x];

	return 0;
}

int Level::ceilingIndexAt(unsigned int x, unsigned int y)
{
	if (y < this->height)
		if (x < this->widths[y])
			return this->ceilingData[y][x];

	return 0;
}

Tile Level::wallTileAt(unsigned int x, unsigned int y)
{
	int wallIndex = wallIndexAt(x, y);
	return this->wallLookup[wallIndex];
}

int Level::getPlayerStartX()
{
	return this->playerStartX;
}

int Level::getPlayerStartY()
{
	return this->playerStartY;
}

double Level::getPlayerStartAngle()
{
	return this->playerStartAngle;
}