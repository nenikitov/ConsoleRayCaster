#pragma once

#include "../PhysicsObject/AbstractPhysicsObject.h"
#include "../Camera/Camera.h"

class AbstractPlayer : public AbstractPhysicsObject
{
	public:
		AbstractPlayer(Scene& scene, double fov);
		virtual void tick(double deltaTime) override = 0;
	protected:
		const Camera CAMERA;
};
