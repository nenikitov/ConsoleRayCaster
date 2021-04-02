#pragma once
#include "../Controller/Controller.h"

class Player
{
	public:
		Player(float positionX = 8.f, float postitionY = 8.f, float angle = 0.f);
	private:
		Controller controller;
		float positionX;
		float positionY;
		float angle;
};