#include "AbstractGameObject.h"

AbstractGameObject::AbstractGameObject(double posX, double posY, double angle)
{
	this->setTransform(posX, posY, angle);
}

void AbstractGameObject::tick(double deltaSeconds) { }

void AbstractGameObject::setTransform(double posX, double posY, double angle)
{
	this->posX = posX;
	this->posY = posY;
	this->angle = angle;
}

double AbstractGameObject::getPosX()
{
	return this->posX;
}

double AbstractGameObject::getPosY()
{
	return this->posY;
}

double AbstractGameObject::getAngle()
{
	return this->angle;
}
