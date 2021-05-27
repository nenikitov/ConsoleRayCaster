#pragma once

#include "../../Abstract/AbstractGameObject.h"
#include "../../../Scene/Scene.h"

class AbstractPhysicsObject : public AbstractGameObject
{
	public:
		AbstractPhysicsObject(double posX, double posY, double angle, Scene& scene);
		virtual void tick(double deltaSeconds) = 0;
	protected:
		const Scene& SCENE;
};
