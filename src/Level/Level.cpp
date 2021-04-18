#include "Level.h"
#include <fstream>
#include <iostream>

Level::Level(std::string levelName)
{
	Json::Value json;
	std::ifstream ifs;
	ifs.open("data/levels/" + levelName);
	Json::CharReaderBuilder builder;
	JSONCPP_STRING errs;

	if (!parseFromStream(builder, ifs, &json, &errs))
		throw std::invalid_argument(levelName + " - recieved invalid JSON file");

	this->height = json["tileData"]["wall"].size();

	if (this->height == 0)
		throw std::invalid_argument(levelName + " - the height of a level is 0");

	this->levelData = new int* [this->height];
	this->widths = new unsigned int[height];

	for (unsigned int y = 0; y < this->height; y++)
	{
		const unsigned int WIDTH = json["tileData"]["wall"][y].size();

		if (WIDTH == 0)
			throw std::invalid_argument(levelName + " - the width of a level on the line " + std::to_string(y) + " is 0");

		this->widths[y] = WIDTH;
		this->levelData[y] = new int[WIDTH];

		for (unsigned int x = 0; x < WIDTH; x++)
		{
			const unsigned int TILE = json["tileData"]["wall"][y][x].asInt();
		
			if (TILE < 0)
				throw std::invalid_argument(levelName + " - invalid tile index at " + std::to_string(x) + ", " + std::to_string(y));

			this->levelData[y][x] = TILE;
		}
	}
}

int Level::tileIndexAt(unsigned int x, unsigned int y)
{
	if (y < this->height)
		if (x < this->widths[y])
			return this->levelData[y][x];
	
	return 0;
}