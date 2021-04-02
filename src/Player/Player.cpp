#include "Player.h"
#include <corecrt_math_defines.h>
#include <math.h>

Player::Player(float positionX, float positionY, float angle)
{
	this->positionX = positionX;
	this->positionY = positionY;
	this->angle = angle;
}

void Player::update(double deltaTime)
{
	// Update position (Implement collision detection later)
	this->positionX += this->controller.getRightward() * this->MOVE_SPEED * deltaTime;
	this->positionY -= this->controller.getForward() * this->MOVE_SPEED * deltaTime;

	// Update rotation
	this->angle += this->controller.getTurn() * this->TURN_SPEED * deltaTime;
	if (this->angle < 0)
		this->angle = 2 * M_PI + angle;
	else if (this->angle >= 2 * M_PI)
		this->angle = fmod(this->angle, 2 * M_PI);
}
double Player::getPositionX()
{
	return this->positionX;
}
double Player::getPositionY()
{
	return this->positionY;
}
double Player::getAngle()
{
	return this->angle;
}