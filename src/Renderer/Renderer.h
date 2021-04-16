#pragma once
#include "../Player/Player.h"
#include "../Level/Level.h"
#include "../RayCaster/RayCaster.h"
#include "../ConsoleHandler/ConsoleColors.h"

class Renderer
{
	public:
		Renderer(Player& player, Level& level);
		CHAR_INFO* render(unsigned short resolutionX, unsigned short resolutionY, unsigned short fov, unsigned short wallHeight);
	private:
		RayCaster rayCaster;
		Player& player;
		Level& level;
		Tile tile = Tile("bricks.tl.json");
};