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
		throw std::invalid_argument("Recieved invalid JSON file");

	this->height = json["tileData"]["wall"].size();
	this->levelData = new int* [this->height];
	this->widths = new unsigned int[height];

	for (unsigned int y = 0; y < this->height; y++)
	{
		const unsigned int WIDTH = json["tileData"]["wall"][y].size();
		this->widths[y] = WIDTH;
		this->levelData[y] = new int[WIDTH];

		for (unsigned int x = 0; x < WIDTH; x++)
		{
			const unsigned int TILE = json["tileData"]["wall"][y][x].asInt();
			this->levelData[y][x] = TILE;
		}
	}
}

int Level::tileAt(unsigned int x, unsigned int y)
{
	if (y < this->height)
		if (x < this->widths[y])
			return this->levelData[y][x];
	
	return 0;
}