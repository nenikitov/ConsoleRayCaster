#include "Level.h"
#include <fstream>
#include <iostream>


Level::Level(std::string levelName)
{
	// Load JSON data from file
	Json::Value json;
	std::ifstream ifs;
	ifs.open("data/levels/" + levelName);
	Json::CharReaderBuilder builder;
	JSONCPP_STRING errs;

	// ERROR CATCHING - Invalid file
	if (!parseFromStream(builder, ifs, &json, &errs))
		throw std::invalid_argument(levelName + " - recieved invalid JSON file");

	this->playerStartX = json["player"]["x"].asInt();
	this->playerStartY = json["player"]["y"].asInt();
	this->playerStartAngle = (double)json["player"]["angle"].asInt() / 0.017453292; // Transform degrees to radians

	// Get height of the level
	this->height = json["tileData"]["wall"].size();
	// ERROR CATCHING - Height is 0
	if (this->height == 0)
		throw std::invalid_argument(levelName + " - the height of a level is 0");

	// ERROR CATCHING - Inconsistent heights for wall, ceiling and floor data
	if (this->height != json["tileData"]["floor"].size() ||  this->height != json["tileData"]["ceiling"].size())
		throw std::invalid_argument(levelName + " - the height of a level is different for walls, ceiling and floor");

	// Initialize pointers
	this->wallData = new int* [this->height];
	this->floorData = new int* [this->height];
	this->ceilingData = new int* [this->height];
	this->widths = new unsigned int[height];

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
				throw std::invalid_argument(levelName + " - invalid wall data index at " + std::to_string(x) + ", " + std::to_string(y));
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

int Level::tileIndexAt(unsigned int x, unsigned int y)
{
	if (y < this->height)
		if (x < this->widths[y])
			return this->wallData[y][x];
	
	return 0;
}