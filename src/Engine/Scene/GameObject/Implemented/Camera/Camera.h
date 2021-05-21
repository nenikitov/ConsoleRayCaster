#pragma once

#include "../../Abstract/AbstractGameObject.h"

class Camera : public AbstractGameObject
{
	public:
		Camera(double posX, double posY, double angle, double fov);
		double getFov();
		void setFov(double fov);
	private:
		double fov;
};
