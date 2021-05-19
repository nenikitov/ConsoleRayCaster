#pragma once

class AbstractGameObject
{
	public:
		AbstractGameObject(double posX, double posY, double angle);
		void setTransform(double posX, double posY, double angle);
		double getPosX();
		double getPosY();
		double getAngle();
	protected:
		double posX = 0;
		double posY = 0;
		double angle = 0;
};
