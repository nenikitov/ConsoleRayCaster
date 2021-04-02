#pragma once
#include "../Controller/Controller.h"

class Player
{
	public:
		Player(float positionX = 8.f, float positionY = 8.f, float angle = 0.f);
		void update(double deltaTime);
		Controller controller;
	private:
		
		float positionX;
		float positionY;
		float angle;
};