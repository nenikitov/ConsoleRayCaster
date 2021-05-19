#include "AbstractActor.h"

AbstractActor::AbstractActor(double posX, double posY, double angle)
{
	this->setTransform(posX, posY, angle);
}

void AbstractActor::setTransform(double posX, double posY, double angle)
{
	this->posX = posX;
	this->posY = posY;
	this->angle = angle;
}

double AbstractActor::getPosX()
{
	return this->posX;
}

double AbstractActor::getPosY()
{
	return this->posY;
}

double AbstractActor::getAngle()
{
	return this->angle;
}
