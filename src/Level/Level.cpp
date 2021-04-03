#include "Level.h"
#include <fstream>
#include <iostream>

Level::Level(std::string levelName)
{
	char currentChar;
	std::string word = "";
	unsigned int value;
	unsigned int row = 0;

	this->tiles.push_back({});

	std::string path = "data/levels/" + levelName;
	std::fstream fileData(path, std::fstream::in);
	while (fileData >> std::noskipws >> currentChar)
	{
		if (currentChar == ' ' || currentChar == '\n')
		{
			if (word.length() != 0)
			{
				value = std::stoi(word);

				this->tiles[row].push_back(value);
				if (currentChar == '\n')
				{
					this->tiles.push_back({});
					row++;
				}
				
				word = "";
			}
		}
		else
			word += currentChar;
	}
	this->tiles[row].push_back(value);
}

int Level::tileAt(unsigned int x, unsigned int y)
{
	if (y < tiles.size())
		if (x < tiles[y].size())
			return this->tiles[y][x];
	return 0;
}