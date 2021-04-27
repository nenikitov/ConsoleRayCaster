#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "../Tile/Tile.h"
#include "../JsonCpp/json/json.h"

class Level
{
	public:
		/// <summary>
		/// Initialize the level
		/// </summary>
		/// <param name="levelName">The name of the level (should not contain ".lvl.json")</param>
		/// <returns></returns>
		Level(std::string levelName);
		/// <summary>
		/// Find the index of a wall tile in the look up at specific coordinates
		/// </summary>
		/// <param name="x">Coordinate X</param>
		/// <param name="y">Coordinate Y</param>
		/// <returns>The index of a wall tile in the lookup</returns>
		int wallIndexAt(unsigned int x, unsigned int y);
		/// <summary>
		/// Find the index of a floor tile in the look up at specific coordinates
		/// </summary>
		/// <param name="x">Coordinate X</param>
		/// <param name="y">Coordinate Y</param>
		/// <returns>The index of a floor tile in the lookup</returns>
		int floorIndexAt(unsigned int x, unsigned int y);
		/// <summary>
		/// Find the index of a ceiling tile in the look up at specific coordinates
		/// </summary>
		/// <param name="x">Coordinate X</param>
		/// <param name="y">Coordinate Y</param>
		/// <returns>The index of a ceiling tile in the lookup</returns>
		int ceilingIndexAt(unsigned int x, unsigned int y);
		/// <summary>
		/// Find the wall tile at specific coordinates
		/// </summary>
		/// <param name="x">Coordinate X</param>
		/// <param name="y">Coordinate Y</param>
		/// <returns>Wall tile object</returns>
		Tile wallTileFrom(unsigned int i);
		/// <summary>
		/// Find the floor tile at specific coordinates
		/// </summary>
		/// <param name="x">Coordinate X</param>
		/// <param name="y">Coordinate Y</param>
		/// <returns>Floor tile object</returns>
		Tile floorTileFrom(unsigned int i);
		/// <summary>
		/// Find the ceiling tile at specific coordinates
		/// </summary>
		/// <param name="x">Coordinate X</param>
		/// <param name="y">Coordinate Y</param>
		/// <returns>Ceiling tile object</returns>
		Tile ceilingTileFrom(unsigned int i);
		/// <summary>
		/// Get the location where the player should start
		/// </summary>
		/// <returns>The X coordinate of player start</returns>
		int getPlayerStartX();
		/// <summary>
		/// Get the location where the player should start
		/// </summary>
		/// <returns>The Y coordinate of player start</returns>
		int getPlayerStartY();
		/// <summary>
		/// Get the location where the player should start
		/// </summary>
		/// <returns>The angle of player start</returns>
		double getPlayerStartAngle();
	private:
		Tile* wallLookup;
		Tile* floorLookup;
		Tile* ceilingLookup;
		unsigned int wallTiles = 0;
		unsigned int floorTiles = 0;
		unsigned int ceilingTiles = 0;
		int** wallData;
		int** floorData;
		int** ceilingData;
		unsigned int height;
		unsigned int* widths;
		int playerStartX;
		int playerStartY;
		double playerStartAngle;
};