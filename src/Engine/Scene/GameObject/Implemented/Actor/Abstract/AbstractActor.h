#pragma once

#include "../../../Abstract/AbstractGameObject.h"

class AbstractActor : public AbstractGameObject
{
	public:
		AbstractActor(double posX, double posY, double angle);
		virtual void act(double deltaTime) = 0;
		void setTransform(double posX, double posY, double angle);
		double getPosX();
		double getPosY();
		double getAngle();
	protected:
		double posX = 0;
		double posY = 0;
		double angle = 0;
};
