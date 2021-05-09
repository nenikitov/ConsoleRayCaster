#pragma once
#include "../Player/Player.h"
#include "../Level/Level.h"
#include "../RayCaster/RayCaster.h"
#include "../ConsoleHandler/ConsoleColors.h"

class Renderer
{
	public:
		/// <summary>
		/// Initialize the renderer
		/// </summary>
		/// <param name="player">Reference to the player from who the rendering will be performed</param>
		/// <param name="level">Reference to the level where rendering will be performed</param>
		/// <returns>The renderer</returns>
		Renderer(Player& player, Level& level);
		/// <summary>
		/// Render the scene
		/// </summary>
		/// <param name="resolutionX">The number of characters on the X axis of the final render</param>
		/// <param name="resolutionY">The number of characters on the Y axis of the final render</param>
		/// <param name="fov">The field of view of the camera in the radians</param>
		/// <param name="wallHeight">The wall height in character</param>
		/// <returns>The character representation of the render</returns>
		CHAR_INFO* render(unsigned short resolutionX, unsigned short resolutionY, unsigned short fov, unsigned short wallHeight);
	private:
		RayCaster rayCaster;
		Player& player;
		Level& level;
		Tile testTile = Tile("test");
};