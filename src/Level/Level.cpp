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
	{
		throw std::invalid_argument("Recieved invalid JSON file");
	}

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

	/*
	char currentChar;
	std::string word = "";
	unsigned int value;
	unsigned int row = 0;

	tiles.push_back({});

	std::string path = "data/levels/" + levelName;
	std::fstream fileData(path, std::fstream::in);
	while (fileData >> std::noskipws >> currentChar)
	{
		if (currentChar == ' ' || currentChar == '\n')
		{
			if (word.length() != 0)
			{
				value = std::stoi(word);

				tiles[row].push_back(value);
				if (currentChar == '\n')
				{
					tiles.push_back({});
					row++;
				}
				
				word = "";
			}
		}
		else
			word += currentChar;
	}
	tiles[row].push_back(value);
	


	//this->height = tiles.size();
	//this->widths = new unsigned int[height];

	
	for (unsigned int y = 0; y < this->height; y++)
	{
		this->widths[y] = tiles[y].size();
		this->levelData[y] = new int[this->widths[y]];
		for (unsigned int x = 0; x < this->widths[y]; x++)
			this->levelData[y][x] = tiles[y][x];
	}
	*/
}

int Level::tileAt(unsigned int x, unsigned int y)
{
	if (y < this->height)
		if (x < this->widths[y])
			return this->levelData[y][x];
	
	return 0;
}