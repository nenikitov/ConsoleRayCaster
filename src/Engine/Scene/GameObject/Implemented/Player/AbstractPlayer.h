#pragma once

#include "../../Abstract/AbstractGameObject.h"
#include "../../../Scene/Scene.h"

class AbstractPlayer : public AbstractGameObject
{
	public:
		AbstractPlayer(double posX, double posY, double angle, Scene& scene);
		virtual void tick(double deltaSeconds) = 0;
	protected:
		const Scene& SCENE;
};
