#pragma once
#include "../Controller/Controller.h"

class Player
{
	public:
		/// <summary>
		/// Initialize the player
		/// </summary>
		/// <param name="positionX">X coordinate of the start position</param>
		/// <param name="positionY">Y coordinate of the start position</param>
		/// <param name="angle">Angle of the start position</param>
		/// <returns>The player</returns>
		Player(float positionX = 8.f, float positionY = 8.f, float angle = 0.f);
		/// <summary>
		/// Update the location and rotation of the player from the controls
		/// </summary>
		/// <param name="deltaTime"></param>
		void update(double deltaTime);
		/// <summary>
		/// Get the location of the player
		/// </summary>
		/// <returns>Position on the X coordinate</returns>
		double getPositionX();
		/// <summary>
		/// Get the location of the player
		/// </summary>
		/// <returns>Position on the Y coordinate</returns>
		double getPositionY();
		/// <summary>
		/// Get the rotation of the player
		/// </summary>
		/// <returns>Angle</returns>
		double getAngle();
	private:
		Controller controller;
		const double MOVE_SPEED = 2;
		const double TURN_SPEED = 2;
		double positionX;
		double positionY;
		double angle;
};