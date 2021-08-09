#pragma once

#include "../../Abstract/AbstractGameObject.h"
#include "../../../Scene/Scene.h"
#include "../../../../RayCaster/RayCaster/RayCaster.h"

class AbstractPhysicsObject : public AbstractGameObject
{
	public:
		AbstractPhysicsObject(double posX, double posY, double angle, double radius, Scene& scene);
		virtual void tick(double deltaSeconds) = 0;
		virtual void moveBy(double deltaX, double deltaY);
	protected:
		Scene& scene;
	private:
		const double RADIUS;
		void moveAlongAxis(bool x, double delta);
};
