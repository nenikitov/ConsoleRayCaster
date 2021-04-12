#pragma once
#include "../Player/Player.h"
#include "../Level/Level.h"
#include "../RayCaster/RayCaster.h"
#include "RenderResult.cpp"

class Renderer
{
	public:
		Renderer(Player& player, Level& level);
		RenderResult render(unsigned short resolutionX, unsigned short resolutionY, unsigned short fov, unsigned short wallHeight);
	private:
		RayCaster rayCaster;
		Player& player;
		Level& level;
};