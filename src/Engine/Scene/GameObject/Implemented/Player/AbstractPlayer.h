#pragma once

#include "../PhysicsObject/AbstractPhysicsObject.h"
#include "../Camera/Camera.h"

class AbstractPlayer : public AbstractPhysicsObject
{
	public:
		AbstractPlayer(Scene& scene, double fov);
	protected:
		const Camera CAMERA;
};
