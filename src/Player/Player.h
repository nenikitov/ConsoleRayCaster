#pragma once
#include "../Controller/Controller.h"

class Player
{
	public:
		Player(float positionX = 8.f, float positionY = 8.f, float angle = 0.f);
		void update(double deltaTime);
		double getPositionX();
		double getPositionY();
		double getAngle();
	private:
		Controller controller;
		const double MOVE_SPEED = 2;
		const double TURN_SPEED = 2;
		double positionX;
		double positionY;
		double angle;
};